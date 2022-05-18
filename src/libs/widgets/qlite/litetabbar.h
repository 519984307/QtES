#ifndef LITETABBAR_H
#define LITETABBAR_H

#include "litewidget.h"
#include "qlite_global.h"

namespace QLite {

class LiteTabBarPrivate;

class QLITE_SHARED_EXPORT LiteTabBar : public LiteWidget
{
    Q_OBJECT

public:
    enum Direction
    {
        Horizontal,
        Vertical
    };
    enum ActionPosition
    {
        Front,
        Middle,
        Back
    };

    explicit LiteTabBar(QWidget *parent = nullptr);
    virtual ~LiteTabBar();

    int addTab(const QString &text);
    int addTab(const QIcon &icon, const QString &text);

    int insertTab(int index, const QString &text);
    int insertTab(int index, const QIcon &icon, const QString &text);

    void removeTab(int index);

    int currentIndex() const;
    int count() const;

    void addAction(QAction *action, ActionPosition position = Middle);

    void setTabEnabled(int index, bool enable);
    void setTabVisible(int index, bool visible);

    void setTabButtonStyle(Qt::ToolButtonStyle style);
    void setActionStyle(QAction *action, Qt::ToolButtonStyle style);
    void setTabSpacing(int spacing);

    void setIconSize(QSize size);

    void setDirection(Direction direction);

signals:
    void currentChanged(int index);

public slots:
    void setCurrentIndex(int index);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    LiteTabBarPrivate *d;
};

} // namespace QLite

#endif // LITETABBAR_H
