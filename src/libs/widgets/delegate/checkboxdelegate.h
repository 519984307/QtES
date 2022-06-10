#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include <QStyledItemDelegate>

#include "widgets/widgets_global.h"

class WIDGETS_EXPORT CheckboxDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit CheckboxDelegate(QObject *parent = nullptr);

    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:
    /**
     * @brief editorClicked Emited when the editor was clicked.
     * @param iRow iRow The row clicked.
     */
    void editorClicked(int iRow);

private slots:
    void commitAndCloseEditor(int);
};

#endif // CHECKBOXDELEGATE_H
