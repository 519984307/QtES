#ifndef SYSVERSIONINFO_H
#define SYSVERSIONINFO_H

#include <string>

namespace Sys {
namespace Version {

static std::string appName()
{
    return "app";
}

static std::string appDisplayName()
{
    return "app";
}

static std::string version()
{
    return "0.0.1";
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
    return "2022-05-23";
}

static std::string buildTime()
{
    return "14:54:13";
}

static std::string commit()
{
    return "commit 900640481467848443a75871040bd0f9fb6f6646";
}

static std::string branch()
{
    return "pansiumgui";
}

static std::string tag()
{
    return "";
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
