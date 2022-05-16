#ifndef CRASHHANDLERSETUP_H
#define CRASHHANDLERSETUP_H

#include <QString>

class CrashHandlerSetup
{
public:
    enum RestartCapability
    {
        EnableRestart,
        DisableRestart
    };

    CrashHandlerSetup(const QString &appName, const QString &organizationName,
                      RestartCapability restartCap = EnableRestart,
                      const QString &executableDirPath = QString());
    ~CrashHandlerSetup();
};

#endif // CRASHHANDLERSETUP_H
