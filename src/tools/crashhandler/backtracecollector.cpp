
#include "backtracecollector.h"

#include <QDebug>
#include <QScopedPointer>
#include <QTemporaryFile>

const char GdbBatchCommands[] = "set height 0\n"
                                "set width 0\n"
                                "thread\n"
                                "thread apply all backtrace full\n";

class BacktraceCollectorPrivate
{
public:
    BacktraceCollectorPrivate() : errorOccurred(false) {}

    bool errorOccurred;
    QScopedPointer<QTemporaryFile> commandFile;
    QProcess debugger;
    QString output;
};

BacktraceCollector::BacktraceCollector(QObject *parent) :
    QObject(parent), d(new BacktraceCollectorPrivate)
{
    connect(&d->debugger, SIGNAL(finished(int, QProcess::ExitStatus)),
            SLOT(onDebuggerFinished(int, QProcess::ExitStatus)));
    connect(&d->debugger, SIGNAL(error(QProcess::ProcessError)),
            SLOT(onDebuggerError(QProcess::ProcessError)));
    connect(&d->debugger, SIGNAL(readyRead()), SLOT(onDebuggerOutputAvailable()));
    d->debugger.setProcessChannelMode(QProcess::MergedChannels);
}

BacktraceCollector::~BacktraceCollector()
{
    delete d;
}

void BacktraceCollector::run(Q_PID pid)
{
    d->debugger.start(QLatin1String("gdb"),
                      QStringList() << QLatin1String("--nw")    // Do not use a window interface.
                                    << QLatin1String("--nx")    // Do not read .gdbinit file.
                                    << QLatin1String("--batch") // Exit after processing options.
                                    << QLatin1String("--command") << createTemporaryCommandFile()
                                    << QLatin1String("--pid") << QString::number(pid));
}

bool BacktraceCollector::isRunning() const
{
    return d->debugger.state() == QProcess::Running;
}

void BacktraceCollector::kill()
{
    d->debugger.kill();
}

void BacktraceCollector::onDebuggerFinished(int exitCode, QProcess::ExitStatus /*exitStatus*/)
{
    if (d->errorOccurred) {
        emit error(QLatin1String("QProcess: ") + d->debugger.errorString());
        return;
    }
    if (exitCode != 0) {
        emit error(QString::fromLatin1("Debugger exited with code %1.").arg(exitCode));
        return;
    }
    emit backtrace(d->output);
}

void BacktraceCollector::onDebuggerError(QProcess::ProcessError /*error*/)
{
    d->errorOccurred = true;
}

QString BacktraceCollector::createTemporaryCommandFile()
{
    d->commandFile.reset(new QTemporaryFile);
    if (!d->commandFile->open()) {
        emit error(QLatin1String("Error: Could not create temporary command file."));
        return QString();
    }
    if (d->commandFile->write(GdbBatchCommands) == -1) {
        emit error(QLatin1String("Error: Could not write temporary command file."));
        return QString();
    }
    d->commandFile->close();
    return d->commandFile->fileName();
}

void BacktraceCollector::onDebuggerOutputAvailable()
{
    const QString newChunk = QString::fromLocal8Bit(d->debugger.readAll());
    d->output.append(newChunk);
    emit backtraceChunk(newChunk);
}
