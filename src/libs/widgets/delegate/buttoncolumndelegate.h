#ifndef BUTTONCOLUMNDELEGATE_H
#define BUTTONCOLUMNDELEGATE_H

#include <QPushButton>
#include <QStyledItemDelegate>
#include <QTableView>
#include <QWidget>

#include "widgets/widgets_global.h"

class WIDGETS_EXPORT ButtonColumnDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ButtonColumnDelegate(QObject *parent = nullptr);
    ~ButtonColumnDelegate();

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;

public slots:
    void cellEntered(const QModelIndex &index);

private:
    QTableView *m_tableView;
    QPushButton *m_button;
    bool m_isOneCellInEditMode;
    QPersistentModelIndex m_currentEditedCellIndex;
};

#endif // BUTTONCOLUMNDELEGATE_H
