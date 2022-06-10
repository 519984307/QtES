#ifndef NUMBERLINEEDITDELEGATE_H
#define NUMBERLINEEDITDELEGATE_H

#include <QModelIndex>
#include <QStyledItemDelegate>

#include "widgets_global.h"

namespace PansimGuiCore {

class WIDGETS_EXPORT NumberLineEditDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit NumberLineEditDelegate(QObject *parent = nullptr);
    virtual ~NumberLineEditDelegate();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

} // namespace PansimGuiCore

#endif // NUMBERLINEEDITDELEGATE_H
