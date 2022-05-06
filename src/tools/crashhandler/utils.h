
#ifndef UTILS_H
#define UTILS_H

#include <QByteArray>
#include <QString>

const char APPLICATION_NAME[] = "Crash Handler";
const char URL_BUGTRACKER[] = "http://www.dfjy-jx.com/";

QByteArray fileContents(const QString &filePath);

#endif // UTILS_H
