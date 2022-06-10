#ifndef RADIOBUTTONDELEGATE_H
#define RADIOBUTTONDELEGATE_H

#include <QStyledItemDelegate>

#include "widgets_global.h"

static const int RadioSelectedRole = Qt::UserRole + 102;
static const int IsRadioRole = Qt::UserRole + 103;

class RadioButtonDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit RadioButtonDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // RADIOBUTTONDELEGATE_H
