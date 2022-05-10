#include "basedialog.h"

#include "framelesshelper.h"
#include "titlebar.h"

namespace Widgets {

BaseDialog::BaseDialog(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window | Qt::WindowSystemMenuHint
                   | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
    resize(1920, 1080);
    setObjectName("allDialog");
    setMouseTracking(true);
    auto *m_vlayout = new QVBoxLayout(this);
    m_centerwidget = new QWidget(this);
    m_title_bar = new TitleBar(this);
    m_title_bar->resize(1024, 48);

    // m_title_bar->setMouseTracking(true);
    // m_centerwidget->setMouseTracking(true);

    m_vlayout->addWidget(m_title_bar);
    m_vlayout->addWidget(m_centerwidget);

    m_vlayout->setMargin(0);
    m_vlayout->setSpacing(0);
    setLayout(m_vlayout);

    init_border();
}

BaseDialog::~BaseDialog() {}

void BaseDialog::set_layout(QLayout *layout)
{
    m_centerwidget->setLayout(layout);
}

void BaseDialog::init_border()
{
    pHelper = new FramelessHelper(this);
    pHelper->activateOn(this);
    pHelper->setWidgetMovable(true);
    pHelper->setWidgetResizable(true);
    pHelper->setRubberBandOnMove(true);
    pHelper->setRubberBandOnResize(true);
}

void BaseDialog::set_title(const QString &title)
{
    m_title_bar->set_title(title);
}
} // namespace Widgets