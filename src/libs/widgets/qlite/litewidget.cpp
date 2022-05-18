#include "litewidget.h"

#include <QPainter>
#include <QStyleOption>

namespace QLite {

LiteWidget::LiteWidget(QWidget *parent) : QWidget(parent) {}

void LiteWidget::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

} // namespace QLite