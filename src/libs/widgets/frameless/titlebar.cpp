#include "titlebar.h"

namespace Widgets {

TitleBar::TitleBar(QWidget *parent) : QWidget(parent)
{
    m_mouse_press = false;
    m_pb_close = new QPushButton(this);
    m_pb_close->setToolTip("Close");
    m_pb_close->setObjectName("pb_close");
    m_pb_max = new QPushButton(this);
    m_pb_max->setToolTip("Maximize");
    m_pb_max->setObjectName("pb_zoom");
    m_pb_min = new QPushButton(this);
    m_pb_min->setToolTip("Minimize");
    m_pb_min->setObjectName("pb_dezoom");

    initTitleBar();
}

TitleBar::~TitleBar() {};

void TitleBar::initTitleBar()
{
    this->setObjectName("frame_title");
    this->setFixedHeight(48);
    QHBoxLayout *hLayout = new QHBoxLayout(this);

    m_spacelabel = new QLabel(this);
    m_spacelabel->setObjectName("title_text");
    QFont font;
    font.setFamily("Sans Serif");
    font.setPointSize(12);
    m_spacelabel->setFont(font);
    m_spacelabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    m_pb_max->setFixedWidth(48);
    m_pb_min->setFixedWidth(48);
    m_pb_close->setFixedWidth(48);
    m_pb_max->setFixedHeight(48);
    m_pb_min->setFixedHeight(48);
    m_pb_close->setFixedHeight(48);
    m_pb_min->setIcon(QIcon(":/title_icon/dezoom.png").pixmap(16, 16));
    m_pb_close->setIcon(QIcon(":/title_icon/close.png").pixmap(16, 16));

    QWidget *pWindow = this->window();
    pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
    if (pWindow->isMaximized()) {
        this->setMaxiBtnIcon(QIcon(":/title_icon/rezoom.png"));
    } else {
        this->setMaxiBtnIcon(QIcon(":/title_icon/zoom.png"));
    }

    connect(m_pb_close, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pb_max, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pb_min, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    hLayout->addWidget(m_spacelabel);
    hLayout->addWidget(m_pb_min);
    hLayout->addWidget(m_pb_max);
    hLayout->addWidget(m_pb_close);

    hLayout->setMargin(0);
    hLayout->setSpacing(0);
    this->setLayout(hLayout);
}

void TitleBar::set_title(const QString &name)
{
    m_spacelabel->setText(name);
    m_spacelabel->setObjectName("Bold");
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_mouse_press = true;
        m_LastMousePosition = event->globalPos();
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
    QWidget *pWindow = this->window();

    if (event->buttons().testFlag(Qt::LeftButton) && m_mouse_press) {
        pWindow->move(pWindow->pos() + (event->globalPos() - m_LastMousePosition));
        m_LastMousePosition = event->globalPos();
    }
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_mouse_press = false;
    }
}

void TitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());

    QWidget *pWindow = this->window();

    if (pWindow->isTopLevel()) {
        if (pButton == m_pb_min) {
            pWindow->showMinimized();
            pWindow->setWindowState(Qt::WindowNoState);
        } else if (pButton == m_pb_max) {
            pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
            if (pWindow->isMaximized()) {
                this->setMaxiBtnIcon(QIcon(":/title_icon/rezoom.png"));
            } else {
                this->setMaxiBtnIcon(QIcon(":/title_icon/zoom.png"));
            }

        } else if (pButton == m_pb_close) {
            pWindow->close();
        }
    }
}

void TitleBar::updateMaximize()
{
    QWidget *pWindow = this->window();

    if (pWindow->isTopLevel()) {
        bool bMaximize = pWindow->isMaximized();
        if (bMaximize) {
            m_pb_max->setToolTip(tr("Restore"));
            m_pb_max->setProperty("maximizeProperty", "restore");
        } else {
            m_pb_max->setToolTip(tr("Maximize"));
            m_pb_max->setProperty("maximizeProperty", "maximize");
        }

        m_pb_max->setStyle(QApplication::style());
    }
}

void TitleBar::setMiniBtnIcon(const QIcon &icon)
{
    m_pb_min->setIcon(icon.pixmap(m_pb_min->size()));
}

void TitleBar::setMaxiBtnIcon(const QIcon &icon)
{
    m_pb_max->setIcon(icon.pixmap(m_pb_max->size()));
}

void TitleBar::setCloseBtnIcon(const QIcon &icon)
{
    m_pb_close->setIcon(icon.pixmap(m_pb_close->size()));
}

} // namespace Widgets