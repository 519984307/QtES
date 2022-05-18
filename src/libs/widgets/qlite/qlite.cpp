#include "qlite.h"

#include <QApplication>
#include <QColor>
#include <QFile>
#include <QPalette>
#include <QtCore>

namespace QLite {

void setStyle(const QString &style)
{
    QFile file(style);
    if (file.open(QFile::ReadOnly)) {
        QString qss = QLatin1String(file.readAll());
        qApp->setStyleSheet(qss);
        file.close();
    } else {
        qApp->setStyleSheet(style);
    }
}

QString loadStyle(const QString &filename)
{
    QFile stylefile(filename);
    if (stylefile.open(QFile::ReadOnly)) {
        QTextStream stream(&stylefile);
        QString stylesheet = stream.readAll();
        return stylesheet;
    } else {
        return QString("");
    }
}

} // namespace QLite
