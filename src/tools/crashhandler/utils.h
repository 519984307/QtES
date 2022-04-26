
#ifndef UTILS_H
#define UTILS_H

#include <QByteArray>
#include <QString>

const char APPLICATION_NAME[] = "Crash Handler";
const char URL_BUGTRACKER[] = "https://bugreports.qt-project.org/";

QByteArray fileContents(const QString &filePath);

#endif // UTILS_H
