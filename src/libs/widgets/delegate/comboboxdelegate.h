#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QStyledItemDelegate>

#include "widgets/widgets_global.h"

class WIDGETS_EXPORT ComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    // Types
    struct Item final
    {
        QString text;
        QIcon icon;
        QVariant data;
    };
    struct Items final : public QVector<Item>
    {
        void sort() noexcept
        {
            //            QCollator collator;
            //            collator.setCaseSensitivity(Qt::CaseInsensitive);
            //            collator.setIgnorePunctuation(false);
            //            collator.setNumericMode(true);

            //            std::sort(begin(), end(),
            //                      [&collator](const Item &lhs, const Item &rhs) { return collator(lhs.text, rhs.text); });
        }
    };

public:
    // Constructors / Destructor
    explicit ComboBoxDelegate(bool editable = false, QObject *parent = nullptr) noexcept;
    ComboBoxDelegate(const ComboBoxDelegate &other) = delete;
    ~ComboBoxDelegate() noexcept;

    // Inherited from QStyledItemDelegate
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

    // Operator Overloadings
    ComboBoxDelegate &operator=(const ComboBoxDelegate &rhs) = delete;

private: // Data
    bool mEditable;
};

Q_DECLARE_METATYPE(ComboBoxDelegate::Items)

#endif // COMBOBOXDELEGATE_H
