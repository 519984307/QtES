#ifndef LITETABWIDGET_H
#define LITETABWIDGET_H

#include "litewidget.h"
#include "qlite_global.h"

namespace QLite {

class LiteTabBar;
class LiteTabWidgetPrivate;

class QLITE_SHARED_EXPORT LiteTabWidget : public LiteWidget
{
    Q_OBJECT
    Q_PROPERTY(TabPosition tabPosition READ tabPosition WRITE setTabPosition)

public:
    explicit LiteTabWidget(QWidget *parent = nullptr);
    ~LiteTabWidget();

    int addTab(QWidget *widget, const QString &);
    int addTab(QWidget *widget, const QIcon &icon, const QString &label);

    int insertTab(int index, QWidget *widget, const QString &);
    int insertTab(int index, QWidget *widget, const QIcon &icon, const QString &label);

    void removeTab(int index);

    int currentIndex() const;
    QWidget *currentWidget() const;
    QWidget *widget(int index) const;
    int indexOf(QWidget *widget) const;
    int count() const;

    void setTabEnabled(QWidget *widget, bool enable);
    void setTabVisible(QWidget *widget, bool visible);

    LiteTabBar *tabBar(void) const;

    enum TabPosition
    {
        North,
        South,
        West,
        East
    };

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    // TODO
#else
    Q_ENUM(TabPosition)
#endif

    TabPosition tabPosition() const;
    void setTabPosition(TabPosition);

    void setTabButtonStyle(Qt::ToolButtonStyle style);
    void setTabSpacing(int spacing);

signals:

public slots:

private:
    LiteTabWidgetPrivate *d;
};

} // namespace QLite

#endif // LITETABWIDGET_H
