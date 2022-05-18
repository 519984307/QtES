#include "litescreen.h"

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
#    include <QApplication>
#    include <QDesktopWidget>
#else
#    include <QGuiApplication>
#    include <QScreen>
#endif

namespace QLite {

LiteScreen::LiteScreen()
{
    m_screenRects.clear();

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    QDesktopWidget *desktop = QApplication::desktop();
    int screenCnt = desktop->screenCount();

    for (int i = 0; i < screenCnt; i++) {
        QRect rect = desktop->availableGeometry(i);
        m_screenRects.append(rect);
    }
#else
    QList<QScreen *> screenList = QGuiApplication::screens();
    foreach (QScreen *screen, screenList) {
#    if defined(Q_OS_WIN)
        m_screenRects.append(screen->availableGeometry());
#    else
        m_screenRects.append(screen->virtualGeometry());
#    endif
    }
#endif
}

int LiteScreen::currentScreen(const int x)
{
    int width;

    for (int i = 0; i < m_screenRects.count(); i++) {
        width = m_screenRects.at(i).x() + m_screenRects.at(i).width();

        if (x > width) {
            continue;
        }
        return i;
    }

    return 0;
}

QRect LiteScreen::screenRect(const int current)
{
    if (current >= m_screenRects.count()) {
        return m_screenRects.at(0);
    } else {
        return m_screenRects.at(current);
    }
}

QRect LiteScreen::normalRect()
{
    QRect geom;
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    geom = QApplication::desktop()->availableGeometry();
#else
#    if defined(Q_OS_WIN)
    geom = QGuiApplication::primaryScreen()->availableGeometry();
#    else
    geom = QGuiApplication::primaryScreen()->virtualGeometry();
#    endif
#endif
    return QRect(geom.x() + 100, geom.y() + 100, 2 * geom.width() / 3, 2 * geom.height() / 3);
}

} // namespace QLite