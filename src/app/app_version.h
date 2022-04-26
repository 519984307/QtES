#ifndef APP_VERSION_H
#define APP_VERSION_H

namespace Core {
namespace Constants {

#define STRINGIFY_INTERNAL(x) #x
#define STRINGIFY(x) STRINGIFY_INTERNAL(x)

#define APP_VERSION 0.0.1
#define APP_VERSION_STR STRINGIFY(APP_VERSION)

#define APP_VERSION_MAJOR 0
#define APP_VERSION_MINOR 0
#define APP_VERSION_RELEASE 1

const char * const APP_NAME              = "App";
const char * const APP_VERSION_LONG      = APP_VERSION_STR;
const char * const APP_AUTHOR            = "Guo Bin";
const char * const APP_YEAR              = "2022";

#ifdef APP_VERSION_DESCRIPTION
const char * const APP_VERSION_DESCRIPTION_STR = STRINGIFY(APP_VERSION_DESCRIPTION);
#else
const char * const APP_VERSION_DESCRIPTION_STR = "";
#endif

#ifdef APP_REVISION
const char * const APP_REVISION_STR      = STRINGIFY(APP_REVISION);
#else
const char * const APP_REVISION_STR      = "";
#endif

// changes the path where the settings are saved to
#ifdef APP_SETTINGSVARIANT
const char * const APP_SETTINGSVARIANT_STR      = STRINGIFY(APP_SETTINGSVARIANT);
#else
const char * const APP_SETTINGSVARIANT_STR      = "PansimGUI";
#endif

#ifdef APP_COPY_SETTINGS_FROM_VARIANT
const char * const APP_COPY_SETTINGS_FROM_VARIANT_STR = STRINGIFY(APP_COPY_SETTINGS_FROM_VARIANT);
#else
const char * const APP_COPY_SETTINGS_FROM_VARIANT_STR = "DJEL";
#endif


#undef APP_VERSION
#undef APP_VERSION_STR
#undef STRINGIFY
#undef STRINGIFY_INTERNAL

} // Constants
} // Core

#endif //APP_VERSION_H
