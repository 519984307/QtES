
#include "crashhandler.h"
#include "utils.h"

#include <QApplication>
#include <QFile>
#include <QProcess>
#include <QString>
#include <QStyle>
#include <QTextStream>

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

// Called by signal handler of qtcreator.
// Usage: $0 <name of signal causing the crash>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName(QLatin1String(APPLICATION_NAME));
    app.setWindowIcon(QApplication::style()->standardIcon(QStyle::SP_MessageBoxCritical));

    // Check usage.
    Q_PID parentPid = getppid();
    QString parentExecutable = QFile::symLinkTarget(QString::fromLatin1("/proc/%1/exe")
        .arg(QString::number(parentPid)));
//    if (argc > 2 || !parentExecutable.contains(QLatin1String("qtcreator"))) {
//        QTextStream err(stderr);
//        err << QString::fromLatin1("This crash handler will be called by Qt Creator itself. "
//                                   "Do not call this manually.\n");
//        return EXIT_FAILURE;
//    }

    // Run.
    CrashHandler *crashHandler = new CrashHandler(parentPid, app.arguments().at(1));
    crashHandler->run();

    return app.exec();
}
