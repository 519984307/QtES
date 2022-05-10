#ifndef TITLE_BAR_H
#define TITLE_BAR_H

#include <QtGui>

namespace Widgets {

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();

    void setMiniBtnIcon(const QIcon &icon);
    void setMaxiBtnIcon(const QIcon &icon);
    void setCloseBtnIcon(const QIcon &icon);

    void set_title(const QString &);

private slots:
    void onClicked();

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void updateMaximize();
    void initTitleBar();
    QLabel *m_spacelabel;

    QPoint m_LastMousePosition;
    bool m_mouse_press;

    QPushButton *m_pb_close;
    QPushButton *m_pb_max;
    QPushButton *m_pb_min;
    QLabel *m_lb_title;
};

} // namespace Widgets

#endif