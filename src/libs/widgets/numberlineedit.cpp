#include "numberlineedit.h"

#include <QDoubleValidator>

NumberLineEdit::NumberLineEdit(QWidget *parent) : QLineEdit(parent)
{
    init();
}

NumberLineEdit::NumberLineEdit(double value, QWidget *parent) : QLineEdit(parent)
{
    init();
}

NumberLineEdit::NumberLineEdit(double bottom, double top, int decimals, QWidget *parent) :
    QLineEdit(parent), m_bottom(bottom), m_top(top), m_decimals(decimals)
{
    init();
}

NumberLineEdit::NumberLineEdit(double value, double bottom, double top, int decimals, QWidget *parent) :
    QLineEdit(parent), m_bottom(bottom), m_top(top), m_decimals(decimals)
{
    init();
}

void NumberLineEdit::setRange(double bottom, double top, int decimals)
{
    bool changed = false;
    if (m_bottom != bottom) {
        m_bottom = bottom;
        changed = true;
        emit bottomChanged(m_bottom);
    }

    if (m_top != top) {
        m_top = top;
        changed = true;
        emit topChanged(m_top);
    }

    if (m_decimals != decimals) {
        m_decimals = decimals;
        changed = true;
        emit decimalsChanged(m_decimals);
    }

    if (changed)
        emit rangeChanged();
}

void NumberLineEdit::setBottom(double bottom)
{
    setRange(bottom, top(), decimals());
}

void NumberLineEdit::setTop(double top)
{
    setRange(bottom(), top, decimals());
}

void NumberLineEdit::setDecimals(int decimals)
{
    setRange(bottom(), top(), decimals);
}

void NumberLineEdit::setValue(double value)
{
    this->setText(QString::number(value));
}

double NumberLineEdit::value() const
{
    return this->text().toDouble();
}

void NumberLineEdit::init()
{
    QDoubleValidator *valid = new QDoubleValidator(m_bottom, m_top, m_decimals, this);
    valid->setNotation(QDoubleValidator::StandardNotation);

    this->setValidator(valid);
    this->setAlignment(Qt::AlignRight | Qt::AlignTrailing | Qt::AlignVCenter);

    this->setValue(0);
}
