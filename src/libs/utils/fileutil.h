#ifndef __FILEUTIL_H__
#define __FILEUTIL_H__

#include <QString>

#include "utils_global.h"

namespace Utils {

class UTILSSHARED_EXPORT FileUtil
{
public:
    static QString getComputerName();

    static QString getAppDirPath();
    static QString getAppFilePath();
    static QString getJobsAbsDir();
    static QString getScriptsAbsPath();
    static QString getConfigFilePath();

    static bool fileExist(const QString &filename);
    static bool removeFile(const QString &filename);
    static bool copyFile(const QString &srcFile, const QString &dstFile);

    static bool dirExist(const QString &path);
    static bool makeDir(const QString &path);
    static bool removeDir(const QString &path);
    static bool clearDir(const QString &path);

    static QString getCurrentTimeString();
};
} // namespace Utils
#endif // __FILEUTIL_H__