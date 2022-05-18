#include "litewindow.h"

#include "litebar.h"
#include "litescreen.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QToolButton>

namespace QLite {

class LiteWindowPrivate : public QObject
{
    Q_OBJECT

public:
    LiteWindowPrivate();
    ~LiteWindowPrivate();

    LiteBar *m_liteBar;
    QStatusBar *m_statusBar;
    QMenuBar *m_menuBar;
    QHBoxLayout *m_layout;

public slots:
    void slotResizable(bool resizable);
};

LiteWindowPrivate::LiteWindowPrivate() : m_liteBar(nullptr), m_statusBar(nullptr), m_menuBar(nullptr), m_layout(nullptr)
{}

LiteWindowPrivate::~LiteWindowPrivate()
{
    m_statusBar = nullptr;
}

void LiteWindowPrivate::slotResizable(bool resizable)
{
    if (m_statusBar) {
        m_statusBar->setSizeGripEnabled(resizable);
    }
}

LiteWindow::LiteWindow(QWidget *parent, Qt::WindowFlags f) : QMainWindow(parent), d(new LiteWindowPrivate())
{
    QMainWindow::setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint
                                | Qt::WindowMaximizeButtonHint | Qt::Window | f);
    d->m_liteBar = new LiteBar(this);
    QObject::connect(d->m_liteBar, SIGNAL(sigWidgetResizable(bool)), d, SLOT(slotResizable(bool)));

    QWidget *menuWidget = new QWidget(this);
    d->m_layout = new QHBoxLayout();
    d->m_layout->setSpacing(0);
    d->m_layout->setMargin(0);
    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->setContentsMargins(2, 0, 2, 0);
    mainLayout->setSpacing(1);
    mainLayout->addWidget(d->m_liteBar->logoButton(), 0, Qt::AlignCenter);
    mainLayout->addLayout(d->m_layout);
    mainLayout->addWidget(d->m_liteBar->titleLabel(), 0, Qt::AlignCenter);
    mainLayout->addStretch();
    mainLayout->addWidget(d->m_liteBar->sysToolBar(), 0, Qt::AlignTop);
    menuWidget->setLayout(mainLayout);
    menuWidget->setObjectName(QLatin1String("qlite_titlebar"));
    d->m_liteBar->setTitleBar(menuWidget);

    setMenuWidget(menuWidget);

    setMouseTracking(true);
    QRect geom = LiteScreen::normalRect();
    resize(geom.width(), geom.height());
    raise();
    activateWindow();

    setObjectName(QLatin1String("qlite_window"));
}

LiteWindow::~LiteWindow()
{
    delete d;
}

LiteBar *LiteWindow::liteBar() const
{
    return d->m_liteBar;
}

QMenuBar *LiteWindow::menuBar() const
{
    if (d->m_menuBar == nullptr) {
        d->m_menuBar = new QMenuBar();
#if !defined(Q_OS_WIN)
        d->m_menuBar->setNativeMenuBar(false);
        d->m_menuBar->setVisible(true);
#endif
        d->m_layout->addWidget(d->m_menuBar, 0, Qt::AlignCenter);
        d->m_layout->addStretch();
    }
    return d->m_menuBar;
}

void LiteWindow::setMenuBar(QMenuBar *menuBar)
{
    if (d->m_menuBar == menuBar || menuBar == nullptr) {
        return;
    }
    if (d->m_menuBar) {
        d->m_layout->removeWidget(d->m_menuBar);
        delete d->m_menuBar;
        d->m_menuBar = menuBar;
        d->m_layout->insertWidget(0, d->m_menuBar, 0, Qt::AlignCenter);
    } else {
        d->m_menuBar = menuBar;
        d->m_layout->addWidget(d->m_menuBar, 0, Qt::AlignCenter);
        d->m_layout->addStretch();
    }
#if !defined(Q_OS_WIN)
    d->m_menuBar->setNativeMenuBar(false);
    d->m_menuBar->setVisible(true);
#endif
}

QStatusBar *LiteWindow::statusBar() const
{
    d->m_statusBar = QMainWindow::statusBar();
    return d->m_statusBar;
}

void LiteWindow::setStatusBar(QStatusBar *statusbar)
{
    d->m_statusBar = statusbar;
    QMainWindow::setStatusBar(statusbar);
}

void LiteWindow::setFixedSize(const QSize &s)
{
    setFixedSize(s.width(), s.height());
}

void LiteWindow::setFixedSize(int w, int h)
{
    d->m_liteBar->setWidgetResizable(false);
    QWidget::setFixedSize(w, h);
}

void LiteWindow::setFixedWidth(int w)
{
    setFixedSize(w, this->height());
}

void LiteWindow::setFixedHeight(int h)
{
    setFixedSize(this->width(), h);
}

void LiteWindow::setWindowFlags(Qt::WindowFlags type)
{
    QMainWindow::setWindowFlags(type);
    d->m_liteBar->updateWidgetFlags();
}

} // namespace QLite

#include "litewindow.moc"