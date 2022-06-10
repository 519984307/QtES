#ifndef NUMBERLINEEDIT_H
#define NUMBERLINEEDIT_H

#include <QLineEdit>

#include "widgets_global.h"

class WIDGETS_EXPORT NumberLineEdit : public QLineEdit
{
    Q_OBJECT

    Q_PROPERTY(double bottom READ bottom WRITE setBottom)
    Q_PROPERTY(double top READ top WRITE setTop)
    Q_PROPERTY(int decimals READ decimals WRITE setDecimals)
    Q_PROPERTY(int value READ value WRITE setValue)

public:
    explicit NumberLineEdit(QWidget *parent = nullptr);
    explicit NumberLineEdit(double value, QWidget *parent = nullptr);
    explicit NumberLineEdit(double bottom, double top, int decimals, QWidget *parent = nullptr);
    explicit NumberLineEdit(double value, double bottom, double top, int decimals, QWidget *parent = nullptr);

    void setRange(double bottom, double top, int decimals = 0);

    void setBottom(double);
    double bottom() const { return m_bottom; }

    void setTop(double);
    double top() const { return m_top; }

    void setDecimals(int);
    int decimals() const { return m_decimals; }

    void setValue(double value);
    double value() const;

private:
    void init();

Q_SIGNALS:
    void bottomChanged(double bottom);
    void topChanged(double top);
    void decimalsChanged(int decimals);
    void rangeChanged();

private:
    double m_bottom {-9999};
    double m_top {9999};
    int m_decimals {4};
};

#endif // NUMBERLINEEDIT_H
