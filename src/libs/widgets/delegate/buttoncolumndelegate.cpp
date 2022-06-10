#include "buttoncolumndelegate.h"

#include <QDebug>
#include <QPainter>
#include <QPushButton>
#include <QStylePainter>
#include <QTableView>

ButtonColumnDelegate::ButtonColumnDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    if (QTableView *tableView = qobject_cast<QTableView *>(parent)) {
        m_tableView = tableView;
        m_button = new QPushButton("...", m_tableView);
        m_button->hide();
        m_tableView->setMouseTracking(true);
        connect(m_tableView, SIGNAL(entered(QModelIndex)), this, SLOT(cellEntered(QModelIndex)));
        m_isOneCellInEditMode = false;
    }
}

ButtonColumnDelegate::~ButtonColumnDelegate() {}

QWidget *ButtonColumnDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
    if (index.model()->headerData(index.column(), Qt::Horizontal, Qt::UserRole).toInt() == 1) {
        QPushButton *btn = new QPushButton(parent);
        btn->setText(index.data().toString());
        return btn;
    } else {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

void ButtonColumnDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.model()->headerData(index.column(), Qt::Horizontal, Qt::UserRole).toInt() == 1) {
        QPushButton *btn = qobject_cast<QPushButton *>(editor);
        btn->setProperty("data_value", index.data());
    } else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

void ButtonColumnDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (index.model()->headerData(index.column(), Qt::Horizontal, Qt::UserRole).toInt() == 1) {
        QPushButton *btn = qobject_cast<QPushButton *>(editor);
        model->setData(index, btn->property("data_value"));
    } else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void ButtonColumnDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.model()->headerData(index.column(), Qt::Horizontal, Qt::UserRole).toInt() == 1) {
        m_button->setGeometry(option.rect);
        m_button->setText(index.data().toString());
        if (option.state == QStyle::State_Selected)
            painter->fillRect(option.rect, option.palette.highlight());
        QPixmap map = QPixmap::grabWidget(m_button);
        painter->drawPixmap(option.rect.x(), option.rect.y(), map);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

void ButtonColumnDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                                const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void ButtonColumnDelegate::cellEntered(const QModelIndex &index)
{
    if (index.model()->headerData(index.column(), Qt::Horizontal, Qt::UserRole) == 1) {
        if (m_isOneCellInEditMode) {
            m_tableView->closePersistentEditor(m_currentEditedCellIndex);
        }
        m_tableView->openPersistentEditor(index);
        m_isOneCellInEditMode = true;
        m_currentEditedCellIndex = index;
    } else {
        if (m_isOneCellInEditMode) {
            m_isOneCellInEditMode = false;
            m_tableView->closePersistentEditor(m_currentEditedCellIndex);
        }
    }
}
