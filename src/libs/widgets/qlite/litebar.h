#ifndef LITEBAR_H
#define LITEBAR_H

#include "qlite_global.h"

#include <QObject>

class QMouseEvent;
class QLabel;
class QToolButton;
class QToolBar;
class QAction;
class QIcon;

namespace QLite {

class LiteBarPrivate;

class QLITE_SHARED_EXPORT LiteBar : public QObject
{
    Q_OBJECT

public:
    explicit LiteBar(QWidget *parent);
    ~LiteBar();

    QWidget *mainWidget() const;
    QLabel *titleLabel() const;
    QToolButton *logoButton() const;
    QWidget *sysToolBar() const;

    void addAction(QAction *action);

    void setCloseIcon(QIcon &icon);
    void setMaximizeIcon(QIcon &icon);
    void setMinimizeIcon(QIcon &icon);
    void setNormalIcon(QIcon &icon);
    void setIconDark(bool dark);

    void setWidgetResizable(bool resizable);
    void setWidgetMovable(bool movable);
    void setWidgetMaximizable(bool maximizable);

    void updateWidgetFlags();

    void setTitleBar(QWidget *widget);

public:
    void emitSigWidgetResizable(bool resizable) { emit sigWidgetResizable(resizable); }
    void emitSigWidgetMovable(bool movable) { emit sigWidgetMovable(movable); }

signals:
    void sigWidgetResizable(bool resizable);
    void sigWidgetMovable(bool movable);

protected:
    virtual bool eventFilter(QObject *object, QEvent *event);

private:
    LiteBarPrivate *d;
};

} // namespace QLite

#endif // LITEBAR_H
