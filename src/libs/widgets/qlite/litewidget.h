#ifndef LITEWIDGET_H
#define LITEWIDGET_H

#include "qlite_global.h"

#include <QWidget>

namespace QLite {

class QLITE_SHARED_EXPORT LiteWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LiteWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *e);
};

} // namespace QLite

#endif // LITEWIDGET_H
