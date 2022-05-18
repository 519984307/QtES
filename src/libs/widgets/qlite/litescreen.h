#ifndef LITESCREEN_H
#define LITESCREEN_H

#include "qlite_global.h"

#include <QList>
#include <QRect>

namespace QLite {

class QLITE_SHARED_EXPORT LiteScreen
{
public:
    LiteScreen();

    int currentScreen(const int x);
    QRect screenRect(const int current);

    static QRect normalRect();

private:
    QList<QRect> m_screenRects;
};

} // namespace QLite

#endif // LITESCREEN_H
