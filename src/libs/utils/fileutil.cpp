#include "fileutil.h"

#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QHostInfo>
#include <QSettings>

namespace Utils {

QString FileUtil::getComputerName()
{
    QString localHostName = QHostInfo::localHostName();
    return localHostName;
}

QString FileUtil::getAppDirPath()
{
    QString path = QCoreApplication::applicationDirPath();
    return path;
}

QString FileUtil::getAppFilePath()
{
    QString path = QCoreApplication::applicationFilePath();
    return path;
}

QString FileUtil::getJobsAbsDir()
{
    return getAppDirPath();
}

QString FileUtil::getScriptsAbsPath()
{
    return getAppDirPath() + "/scripts";
}

QString FileUtil::getConfigFilePath()
{
    QString configFilePath = QCoreApplication::applicationDirPath() + QString("/configs/config.ini");
    return configFilePath;
}

QString FileUtil::getPansimPath()
{
    QString configFile = getConfigFilePath();
    QSettings config(configFile, QSettings::IniFormat);
    config.setIniCodec("UTF-8");

    QString pansimPath = config.value("Settings/PansimPath", "").toString();

    return pansimPath;
}

QString FileUtil::getWorkingPath()
{
    QString configFile = getConfigFilePath();
    QSettings config(configFile, QSettings::IniFormat);
    config.setIniCodec("UTF-8");

    QString workingPath = config.value("Settings/WorkingPath", "").toString();

    return workingPath;
}

bool FileUtil::fileExist(const QString &filename)
{
    bool exist = QFile::exists(filename);
    return exist;
}

bool FileUtil::removeFile(const QString &filename)
{
    bool ok = QFile::remove(filename);
    return ok;
}

bool FileUtil::copyFile(const QString &srcFile, const QString &dstFile)
{
    return QFile::copy(srcFile, dstFile);
}

bool FileUtil::dirExist(const QString &path)
{
    QDir dir(path);
    return dir.exists();
}

bool FileUtil::makeDir(const QString &path)
{
    QDir dir;
    return dir.mkdir(path);
}

bool FileUtil::removeDir(const QString &path)
{
    bool result = true;

    QDir dir(path);
    if (dir.exists(path)) {
        Q_FOREACH (QFileInfo info,
                   dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::AllDirs | QDir::Files,
                                     QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            } else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result)
                return result;
        }
        result = dir.rmdir(path);
    }
    return result;
}

bool FileUtil::clearDir(const QString &path)
{
    bool result = true;

    QDir dir(path);
    if (dir.exists(path)) {
        Q_FOREACH (QFileInfo info,
                   dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::AllDirs | QDir::Files,
                                     QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            } else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result)
                return result;
        }
    }
    return result;
}

QString FileUtil::getCurrentTimeString()
{
    QDateTime dateTime(QDateTime::currentDateTime());
    return dateTime.toString("yyyy_MM_dd_hh_mm_ss");
}
} // namespace Utils
