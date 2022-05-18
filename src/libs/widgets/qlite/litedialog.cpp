#include "litedialog.h"

#include "litebar.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QLayout>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>

namespace QLite {

class LiteDialogPrivate : public QObject
{
    Q_OBJECT

public:
    LiteDialogPrivate();

    LiteBar *m_liteBar;
    QWidget *m_centralWidget;
};

LiteDialogPrivate::LiteDialogPrivate() : m_liteBar(nullptr), m_centralWidget(nullptr) {}

LiteDialog::LiteDialog(QWidget *parent, Qt::WindowFlags f) : QDialog(parent), d(new LiteDialogPrivate())
{
    QDialog::setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint |
                            //                   Qt::WindowMinimizeButtonHint |
                            Qt::Dialog | f);
    d->m_liteBar = new LiteBar(this);
    d->m_centralWidget = new QWidget();
    d->m_centralWidget->setObjectName(QLatin1String("centerwidget"));
    d->m_centralWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QWidget *titleWidget = new QWidget(this);
    titleWidget->setObjectName(QLatin1String("qlite_titlebar"));
    d->m_liteBar->setTitleBar(titleWidget);

    QHBoxLayout *titleLayout = new QHBoxLayout();
    titleLayout->setContentsMargins(2, 0, 2, 0);
    titleLayout->setSpacing(1);
    titleLayout->addWidget(d->m_liteBar->logoButton(), 0, Qt::AlignCenter);
    titleLayout->addWidget(d->m_liteBar->titleLabel(), 0, Qt::AlignCenter);
    titleLayout->addStretch();
    titleLayout->addWidget(d->m_liteBar->sysToolBar(), 0, Qt::AlignTop);
    titleWidget->setLayout(titleLayout);
    titleWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    mainLayout->addWidget(titleWidget);
    mainLayout->addWidget(d->m_centralWidget);

    QDialog::setLayout(mainLayout);

    resize(QSize(400, 200));
    setMouseTracking(true);
    raise();
    activateWindow();

    setObjectName(QLatin1String("qlite_dialog"));
}

LiteDialog::~LiteDialog()
{
    delete d;
}

LiteBar *LiteDialog::liteBar() const
{
    return d->m_liteBar;
}

QLayout *LiteDialog::layout() const
{
    return d->m_centralWidget->layout();
}

void LiteDialog::setLayout(QLayout *layout)
{
    d->m_centralWidget->setLayout(layout);
}

void LiteDialog::setFixedSize(const QSize &s)
{
    setFixedSize(s.width(), s.height());
}

void LiteDialog::setFixedSize(int w, int h)
{
    d->m_liteBar->setWidgetResizable(false);
    QWidget::setFixedSize(w, h);
}

void LiteDialog::setFixedWidth(int w)
{
    setFixedSize(w, this->height());
}

void LiteDialog::setFixedHeight(int h)
{
    setFixedSize(this->width(), h);
}

void LiteDialog::setWindowFlags(Qt::WindowFlags type)
{
    QDialog::setWindowFlags(type);
    d->m_liteBar->updateWidgetFlags();
}

} // namespace QLite

#include "litedialog.moc"