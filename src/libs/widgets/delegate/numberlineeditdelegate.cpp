#include "numberlineeditdelegate.h"

#include "numberlineedit.h"

namespace PansimGuiCore {

NumberLineEditDelegate::NumberLineEditDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

NumberLineEditDelegate::~NumberLineEditDelegate() {}

QWidget *NumberLineEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem & /* option */,
                                              const QModelIndex & /* index */) const
{
    NumberLineEdit *editor = new NumberLineEdit(parent);
    editor->setValidator(new QDoubleValidator(editor));

    return editor;
}

void NumberLineEditDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    auto value = index.model()->data(index, Qt::EditRole).toString();

    auto *line_edit = static_cast<QLineEdit *>(editor);
    line_edit->setText(value);
}

void NumberLineEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    auto *line_edit = static_cast<QLineEdit *>(editor);
    auto value = line_edit->text();

    model->setData(index, value, Qt::EditRole);
}

void NumberLineEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                                  const QModelIndex & /* index */) const
{
    editor->setGeometry(option.rect);
}

} // namespace PansimGuiCore
