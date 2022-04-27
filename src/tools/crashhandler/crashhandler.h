
#ifndef CRASHHANDLER_H
#define CRASHHANDLER_H

#include <QObject>

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

class ApplicationInfo;
class CrashHandlerPrivate;

class CrashHandler : public QObject
{
    Q_OBJECT

public:
    explicit CrashHandler(pid_t pid, const QString &signalName, QObject *parent = 0);
    ~CrashHandler();

    void run();

public slots:
    void onError(const QString &errorMessage);
    void onBacktraceChunk(const QString &chunk);
    void onBacktraceFinished(const QString &backtrace);

    void openBugTracker();
    void restartApplication();
    void debugApplication();

private:
    bool collectRestartAppData();

    enum WaitMode
    {
        WaitForExit,
        DontWaitForExit
    };
    static void runCommand(QStringList commandLine, QStringList environment, WaitMode waitMode);

    CrashHandlerPrivate *d;
};

#endif // CRASHHANDLER_H
