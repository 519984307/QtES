#ifndef QTLITE_H
#define QTLITE_H

#include "qlite_global.h"

#include <QObject>

namespace QLite {

QLITE_SHARED_EXPORT void setStyle(const QString &style);
QLITE_SHARED_EXPORT QString loadStyle(const QString &filename);

} // namespace QLite

#endif // QTLITE_H
