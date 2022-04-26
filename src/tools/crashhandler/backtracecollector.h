
#ifndef BACKTRACECOLLECTOR_H
#define BACKTRACECOLLECTOR_H

#include <QProcess>

class BacktraceCollectorPrivate;

class BacktraceCollector : public QObject
{
    Q_OBJECT
public:
    explicit BacktraceCollector(QObject *parent = 0);
    ~BacktraceCollector();

    void run(Q_PID pid);
    bool isRunning() const;
    void kill();

signals:
    void error(const QString &errorMessage);
    void backtrace(const QString &backtrace);
    void backtraceChunk(const QString &chunk);

private slots:
    void onDebuggerOutputAvailable();
    void onDebuggerFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onDebuggerError(QProcess::ProcessError err);

private:
    QString createTemporaryCommandFile();

    BacktraceCollectorPrivate *d;
};

#endif // BACKTRACECOLLECTOR_H
