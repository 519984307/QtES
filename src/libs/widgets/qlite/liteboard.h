#ifndef LITEBOARD_H
#define LITEBOARD_H

#include "qlite_global.h"

#include <QDialog>

namespace QLite {

class LiteBoardPrivate;

class QLITE_SHARED_EXPORT LiteBoard : public QDialog
{
    Q_OBJECT

public:
    explicit LiteBoard(QWidget *parent = nullptr);
    virtual ~LiteBoard();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    LiteBoardPrivate *d;
};

} // namespace QLite

#endif // LITEBOARD_H
