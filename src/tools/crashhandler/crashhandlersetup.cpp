
#include "crashhandlersetup.h"

#include <QtGlobal>

// porting.h
namespace Utils {
#if QT_VERSION < QT_VERSION_CHECK(5, 14, 0)
constexpr QString::SplitBehavior SkipEmptyParts = QString::SkipEmptyParts;
#else
constexpr Qt::SplitBehaviorFlags SkipEmptyParts = Qt::SkipEmptyParts;
#endif

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
using QHashSeedType = uint;
#else
using QHashSeedType = size_t;
#endif
} // namespace Utils

#if !defined(QT_NO_DEBUG) && defined(Q_OS_LINUX)
#    define BUILD_CRASH_HANDLER
#endif

#define BUILD_CRASH_HANDLER

#ifdef BUILD_CRASH_HANDLER

#    include <sys/prctl.h>
#    include <sys/types.h>
#    include <sys/wait.h>
// #    include <utils/porting.h>

#    include <QApplication>
#    include <QFileInfo>
#    include <QString>
#    include <QStringList>
#    include <errno.h>
#    include <signal.h>
#    include <stdlib.h>
#    include <string.h>
#    include <unistd.h>

// Enable compilation with older header that doesn't contain this constant
// for running on newer libraries that do support it
#    ifndef PR_SET_PTRACER
#        define PR_SET_PTRACER 0x59616d61
#    endif

#    ifdef Q_WS_X11
#        include <X11/Xlib.h>
#        include <qx11info_x11.h>
#    endif

static const char *appNameC = nullptr;
static const char *organizationNameC = nullptr;
static const char *disableRestartOptionC = nullptr;
static const char *crashHandlerPathC = nullptr;
static void *signalHandlerStack = nullptr;

extern "C" void signalHandler(int signal)
{
#    ifdef Q_WS_X11
    // Kill window since it's frozen anyway.
    if (QX11Info::display())
        close(ConnectionNumber(QX11Info::display()));
#    endif
    pid_t pid = fork();
    switch (pid) {
    case -1: // error
        break;
    case 0: // child
        if (disableRestartOptionC) {
            execl(crashHandlerPathC, crashHandlerPathC, strsignal(signal), appNameC,
                  organizationNameC, disableRestartOptionC, (char *)0);
        } else {
            execl(crashHandlerPathC, crashHandlerPathC, strsignal(signal), appNameC,
                  organizationNameC, (char *)0);
        }
        _exit(EXIT_FAILURE);
    default: // parent
        prctl(PR_SET_PTRACER, pid, 0, 0, 0);
        waitpid(pid, 0, 0);
        _exit(EXIT_FAILURE);
        break;
    }
}
#endif // BUILD_CRASH_HANDLER

CrashHandlerSetup::CrashHandlerSetup(const QString &appName, const QString &organizationName,
                                     RestartCapability restartCap, const QString &executableDirPath)
{
#ifdef BUILD_CRASH_HANDLER
    const QString value = "yes"; //qEnvironmentVariable("QTC_USE_CRASH_HANDLER");
    if (value.trimmed().isEmpty())
        return;

    if (!QStringList {"1", "all", "yes"}.contains(value)) {
        const QString binaryName = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
        if (!value.split(",", Utils::SkipEmptyParts).contains(binaryName))
            return;
    }

    appNameC = qstrdup(qPrintable(appName));
    organizationNameC = qstrdup(qPrintable(organizationName));

    if (restartCap == DisableRestart)
        disableRestartOptionC = "--disable-restart";

    const QString execDirPath
        = executableDirPath.isEmpty() ? QCoreApplication::applicationDirPath() : executableDirPath;
    const QString crashHandlerPath = execDirPath + QLatin1String("/crash_handler");
    crashHandlerPathC = qstrdup(qPrintable(crashHandlerPath));

    // Setup an alternative stack for the signal handler. This way we are able to handle SIGSEGV
    // even if the normal process stack is exhausted.
    stack_t ss;
    ss.ss_sp = signalHandlerStack
        = malloc(SIGSTKSZ); // Usual requirements for alternative signal stack.
    if (ss.ss_sp == 0) {
        qWarning("Warning: Could not allocate space for alternative signal stack (%s).",
                 Q_FUNC_INFO);
        return;
    }
    ss.ss_size = SIGSTKSZ;
    ss.ss_flags = 0;
    if (sigaltstack(&ss, 0) == -1) {
        qWarning("Warning: Failed to set alternative signal stack (%s).", Q_FUNC_INFO);
        return;
    }

    // Install signal handler for calling the crash handler.
    struct sigaction sa;
    if (sigemptyset(&sa.sa_mask) == -1) {
        qWarning("Warning: Failed to empty signal set (%s).", Q_FUNC_INFO);
        return;
    }
    sa.sa_handler = &signalHandler;
    // SA_RESETHAND - Restore signal action to default after signal handler has been called.
    // SA_NODEFER - Don't block the signal after it was triggered (otherwise blocked signals get
    // inherited via fork() and execve()). Without this the signal will not be delivered to the
    // restarted App.
    // SA_ONSTACK - Use alternative stack.
    sa.sa_flags = SA_RESETHAND | SA_NODEFER | SA_ONSTACK;
    // See "man 7 signal" for an overview of signals.
    // Do not add SIGPIPE here, QProcess and QTcpSocket use it.
    const int signalsToHandle[] = {SIGILL, SIGABRT, SIGFPE, SIGSEGV, SIGBUS, 0};
    for (int i = 0; signalsToHandle[i]; ++i) {
        if (sigaction(signalsToHandle[i], &sa, 0) == -1) {
            qWarning("Warning: Failed to install signal handler for signal \"%s\" (%s).",
                     strsignal(signalsToHandle[i]), Q_FUNC_INFO);
        }
    }
#else
    Q_UNUSED(appName)
    Q_UNUSED(restartCap)
    Q_UNUSED(executableDirPath)
#endif // BUILD_CRASH_HANDLER
}

CrashHandlerSetup::~CrashHandlerSetup()
{
#ifdef BUILD_CRASH_HANDLER
    delete[] crashHandlerPathC;
    delete[] appNameC;
    free(signalHandlerStack);
#endif
}
