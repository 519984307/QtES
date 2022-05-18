#ifndef LITEMODEBAR_H
#define LITEMODEBAR_H

#include "litetabbar.h"
#include "qlite_global.h"

class QStackedWidget;

namespace QLite {

class LiteModeBarPrivate;

class QLITE_SHARED_EXPORT LiteModeBar : public LiteTabBar
{
    Q_OBJECT

public:
    explicit LiteModeBar(QStackedWidget *modeStack, QWidget *parent = nullptr);
    ~LiteModeBar();

    int addMode(QWidget *widget, const QString &);
    int addMode(QWidget *widget, const QIcon &icon, const QString &label);

    int insertMode(int index, QWidget *widget, const QString &);
    int insertMode(int index, QWidget *widget, const QIcon &icon, const QString &label);

    void removeMode(int index);

    QWidget *currentMode() const;
    QWidget *Mode(int index) const;
    int indexOf(QWidget *widget) const;

    void setModeEnabled(QWidget *widget, bool enable);
    void setModeVisible(QWidget *widget, bool visible);

private:
    LiteModeBarPrivate *d;
};

} // namespace QLite 

#endif // LITEMODEBAR_H
