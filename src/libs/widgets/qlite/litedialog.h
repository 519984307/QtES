#ifndef LITEDIALOG_H
#define LITEDIALOG_H

#include "qlite_global.h"

#include <QDialog>

namespace QLite {

class LiteBar;
class LiteDialogPrivate;

class QLITE_SHARED_EXPORT LiteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LiteDialog(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    virtual ~LiteDialog();

    LiteBar *liteBar() const;

    QLayout *layout() const;
    void setLayout(QLayout *layout);

    void setFixedSize(const QSize &s);
    void setFixedSize(int w, int h);
    void setFixedWidth(int w);
    void setFixedHeight(int h);

    void setWindowFlags(Qt::WindowFlags type);

private:
    LiteDialogPrivate *d;
};

} // namespace QLite

#endif // LITEDIALOG_H
