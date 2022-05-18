
#ifndef QLITE_GLOBAL_H
#define QLITE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QLITE_LIBRARY)
#    define QLITE_SHARED_EXPORT Q_DECL_EXPORT
#else
#    define QLITE_SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QLITE_GLOBAL_H
