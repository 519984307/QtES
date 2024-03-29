
#ifndef HOSTOSINFO_H
#define HOSTOSINFO_H

#include "utils_global.h"

#include <QString>

#ifdef Q_OS_WIN
#    define QTC_HOST_EXE_SUFFIX ".exe"
#else
#    define QTC_HOST_EXE_SUFFIX ""
#endif // Q_OS_WIN

namespace Utils {

class UTILSSHARED_EXPORT HostOsInfo
{
public:
    // Add more as needed.
    enum HostOs
    {
        HostOsWindows,
        HostOsLinux,
        HostOsMac,
        HostOsOtherUnix,
        HostOsOther
    };
    static inline HostOs hostOs();

    enum HostArchitecture
    {
        HostArchitectureX86,
        HostArchitectureAMD64,
        HostArchitectureItanium,
        HostArchitectureArm,
        HostArchitectureUnknown
    };
    static HostArchitecture hostArchitecture();

    static bool isWindowsHost() { return hostOs() == HostOsWindows; }
    static bool isLinuxHost() { return hostOs() == HostOsLinux; }
    static bool isMacHost() { return hostOs() == HostOsMac; }
    static inline bool isAnyUnixHost();

    static QString withExecutableSuffix(const QString &executable)
    {
        QString finalName = executable;
        if (isWindowsHost())
            finalName += QLatin1String(QTC_HOST_EXE_SUFFIX);
        return finalName;
    }

    static Qt::CaseSensitivity fileNameCaseSensitivity()
    {
        return isWindowsHost() ? Qt::CaseInsensitive : Qt::CaseSensitive;
    }

    static QChar pathListSeparator()
    {
        return isWindowsHost() ? QLatin1Char(';') : QLatin1Char(':');
    }

    static Qt::KeyboardModifier controlModifier()
    {
        return isMacHost() ? Qt::MetaModifier : Qt::ControlModifier;
    }
};

HostOsInfo::HostOs HostOsInfo::hostOs()
{
#if defined(Q_OS_WIN)
    return HostOsWindows;
#elif defined(Q_OS_LINUX)
    return HostOsLinux;
#elif defined(Q_OS_MAC)
    return HostOsMac;
#elif defined(Q_OS_UNIX)
    return HostOsOtherUnix;
#else
    return HostOsOther;
#endif
}

bool HostOsInfo::isAnyUnixHost()
{
#ifdef Q_OS_UNIX
    return true;
#else
    return false;
#endif
}

} // namespace Utils

#endif // HOSTOSINFO_H
