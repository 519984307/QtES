#ifndef SYSVERSIONINFO_H
#define SYSVERSIONINFO_H

#include <string>

namespace Sys {
namespace Version {

static std::string appName()
{
    return "@Target_Name@";
}

static std::string appDisplayName()
{
    return "@Target_Name@";
}

static std::string version()
{
    return "@VERSION_FULL_@";
}

static std::string organizationName()
{
    return "DJEL";
}

static std::string organizationDomain()
{
    return "http://www.dfjy-jx.com/";
}

static std::string buildDate()
{
    return "@BUILD_DATE_@";
}

static std::string buildTime()
{
    return "@BUILD_TIME_@";
}

static std::string commit()
{
    return "@BUILD_COMMIT_@";
}

static std::string branch()
{
    return "@BUILD_BRANCH_@";
}

static std::string tag()
{
    return "@BUILD_TAG_@";
}

static std::string fullVersion()
{
    std::string str = appDisplayName() + " version " + version() + ", built on " + buildDate() + " "
                      + buildTime() + ", with " + commit() + " on branch " + branch();

    if (!tag().empty()) {
        //str += " latest_tag " + tag();
    }

    return str;
}

} // namespace Version

} // namespace Sys

#endif
