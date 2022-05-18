#ifndef LITEWINDOW_H
#define LITEWINDOW_H

#include "qlite_global.h"

#include <QMainWindow>

namespace QLite {

class LiteBar;
class LiteWindowPrivate;

class QLITE_SHARED_EXPORT LiteWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LiteWindow(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    virtual ~LiteWindow();

    LiteBar *liteBar() const;

    QMenuBar *menuBar() const;
    void setMenuBar(QMenuBar *menuBar);

    QStatusBar *statusBar() const;
    void setStatusBar(QStatusBar *statusbar);

    void setFixedSize(const QSize &);
    void setFixedSize(int w, int h);
    void setFixedWidth(int w);
    void setFixedHeight(int h);

    void setWindowFlags(Qt::WindowFlags type);

private:
    LiteWindowPrivate *d;
};

} // namespace QLite

#endif // LITEWINDOW_H
