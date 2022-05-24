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
    return "2022-05-24";
}

static std::string buildTime()
{
    return "16:14:15";
}

static std::string commit()
{
    return "commit 0f04cad8599f0fc24da7fe8d2eb1888d679f8020";
}

static std::string branch()
{
    return "main";
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
