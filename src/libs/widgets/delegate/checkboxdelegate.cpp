#include "checkboxdelegate.h"

#include <QApplication>
#include <QCheckBox>
#include <QDebug>
#include <QModelIndex>

CheckboxDelegate::CheckboxDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

QWidget *CheckboxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
    QCheckBox *editor = new QCheckBox(parent);
    connect(editor, SIGNAL(stateChanged(int)), this, SLOT(commitAndCloseEditor(int)));
    return editor;
}

void CheckboxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QCheckBox *checkBox = qobject_cast<QCheckBox *>(editor);
    checkBox->setChecked(index.data().toBool());
}

void CheckboxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QCheckBox *checkBox = static_cast<QCheckBox *>(editor);
    int value = (checkBox->checkState() == Qt::Checked) ? 1 : 0;
    model->setData(index, value, Qt::EditRole);
}

void CheckboxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //retrieve data
    bool data = index.model()->data(index, Qt::DisplayRole).toBool();

    // create CheckBox style
    QStyleOptionButton checkboxstyle;
    QRect checkbox_rect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &checkboxstyle);

    // center
    checkboxstyle.rect = option.rect;
    checkboxstyle.rect.setLeft(option.rect.x() + option.rect.width() / 2 - checkbox_rect.width() / 2);
    // checked or not checked
    if (data)
        checkboxstyle.state = QStyle::State_On | QStyle::State_Enabled;
    else
        checkboxstyle.state = QStyle::State_Off | QStyle::State_Enabled;

    // done! we can draw!
    QApplication::style()->drawControl(QStyle::CE_CheckBox, &checkboxstyle, painter);
}

void CheckboxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
    Q_UNUSED(index);
    QStyleOptionButton checkboxstyle;
    QRect checkbox_rect = QApplication::style()->subElementRect(QStyle::SE_CheckBoxIndicator, &checkboxstyle);

    // center
    checkboxstyle.rect = option.rect;
    checkboxstyle.rect.setLeft(option.rect.x() + option.rect.width() / 2 - checkbox_rect.width() / 2);

    editor->setGeometry(checkboxstyle.rect);
}

void CheckboxDelegate::commitAndCloseEditor(int)
{
    QCheckBox *editor = static_cast<QCheckBox *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}
