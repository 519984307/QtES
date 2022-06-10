#include "comboboxdelegate.h"

#include <QComboBox>

ComboBoxDelegate::ComboBoxDelegate(bool editable, QObject *parent) noexcept :
    QStyledItemDelegate(parent), mEditable(editable)
{}

ComboBoxDelegate::~ComboBoxDelegate() noexcept {}

QWidget *ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QComboBox *cbx = new QComboBox(parent);
    cbx->setFrame(false);
    cbx->setSizePolicy(QSizePolicy::Ignored, cbx->sizePolicy().verticalPolicy());
    cbx->setEditable(mEditable);
    Items items = index.data(Qt::UserRole).value<Items>();
    foreach (const auto &item, items) {
        cbx->addItem(item.icon, item.text, item.data);
    }
    return cbx;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *cbx = static_cast<QComboBox *>(editor);
    QVariant data = index.data(Qt::EditRole);
    int i = cbx->findData(data, Qt::UserRole);
    if ((i >= 0) || (!mEditable)) {
        cbx->setCurrentIndex(i);
    } else {
        //cbx->setCurrentText(data.toString());
    }
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *cbx = static_cast<QComboBox *>(editor);
    if (mEditable) {
        model->setData(index, cbx->currentText(), Qt::EditRole);
    } else {
        //model->setData(index, cbx->currentData(Qt::UserRole), Qt::EditRole);
    }
}

void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                            const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect);
}
