
#include "hostosinfo.h"

#ifdef Q_OS_WIN
#    undef _WIN32_WINNT
#    define _WIN32_WINNT 0x0501 /* WinXP, needed for GetNativeSystemInfo() */
#    include <qt_windows.h>
#endif

using namespace Utils;

HostOsInfo::HostArchitecture HostOsInfo::hostArchitecture()
{
#ifdef Q_OS_WIN
    SYSTEM_INFO info;
    GetNativeSystemInfo(&info);
    switch (info.wProcessorArchitecture) {
    case PROCESSOR_ARCHITECTURE_AMD64:
        return HostOsInfo::HostArchitectureAMD64;
    case PROCESSOR_ARCHITECTURE_INTEL:
        return HostOsInfo::HostArchitectureX86;
    case PROCESSOR_ARCHITECTURE_IA64:
        return HostOsInfo::HostArchitectureItanium;
    case PROCESSOR_ARCHITECTURE_ARM:
        return HostOsInfo::HostArchitectureArm;
    default:
        return HostOsInfo::HostArchitectureUnknown;
    }
#else
    return HostOsInfo::HostArchitectureUnknown;
#endif
}
