#include "liteboard.h"

#include <QMouseEvent>

namespace QLite {

class LiteBoardPrivate
{
public:
    LiteBoardPrivate();

    QPoint m_movePoint;
    bool m_bPressed;
};

LiteBoardPrivate::LiteBoardPrivate() : m_bPressed(false) {}

LiteBoard::LiteBoard(QWidget *parent) : QDialog(parent), d(new LiteBoardPrivate())
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
}

LiteBoard::~LiteBoard()
{
    delete d;
}

void LiteBoard::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        d->m_bPressed = true;
    }
    d->m_movePoint = event->globalPos() - pos();
}

void LiteBoard::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if (event->globalY() == 0) {
        this->move(this->frameGeometry().x(), 100);
    }
    d->m_bPressed = false;
}

void LiteBoard::mouseMoveEvent(QMouseEvent *event)
{
    if (d->m_bPressed) {
        QPoint movePos = event->globalPos();
        move(movePos - d->m_movePoint);
    }
}

} // namespace QLite
