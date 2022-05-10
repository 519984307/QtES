#ifndef BASE_DIALOG_H
#define BASE_DIALOG_H

#include <QtGui>

namespace Widgets {

class TitleBar;
class FramelessHelper;

class BaseDialog : public QWidget
{
    Q_OBJECT

public:
    explicit BaseDialog(QWidget *parent = 0);
    ~BaseDialog();

    void set_title(const QString &);

protected:
    void set_layout(QLayout *layout);

    TitleBar *m_title_bar;
    QWidget *m_centerwidget;

private:
    void init_border();
    FramelessHelper *pHelper;
};
} // namespace Widgets

#endif // BASE_DIALOG_H