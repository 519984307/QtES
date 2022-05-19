#include "splashscreen.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QImage>
#include <QPainter>
#include <QPropertyAnimation>
#include <QSettings>
#include <QtGlobal>
#include <unistd.h>

SplashScreen::SplashScreen(QApplication *app, QWidget *parent) :
    QSplashScreen(parent),
    m_app(app),
    m_progressBar(new QProgressBar(this)),
    m_progressColor(Qt::green),
    m_fontColor(Qt::green),
    m_opacity(1)
{
    // always top , frameless window and not display on task bar
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);
    // transparent window
    this->setAttribute(Qt::WA_TranslucentBackground);
    // this->setAttribute(Qt::WA_DeleteOnClose);

    initStyle();
}

SplashScreen::~SplashScreen()
{
    // qDebug() << __func__;
}

void SplashScreen::setProgressRange(int min, int max)
{
    m_progressBar->setRange(min, max);
    m_progressBar->setValue(0); // m_progressBar Default vaule is -1
}

void SplashScreen::setProgressValue(int value)
{
    m_progressBar->setValue(value);
    usleep(200000);
}

void SplashScreen::finish(QWidget *w)
{
    this->clearMessage();

    QPropertyAnimation *animation = new QPropertyAnimation(this, "opacity");
    connect(animation, SIGNAL(finished()), this, SLOT(close()));
    animation->setDuration(2000);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();

    // QSplashScreen::finish(w);
}

float SplashScreen::opacity() const
{
    return m_opacity;
}

void SplashScreen::setOpacity(const float opacity)
{
    if (opacity > 1) {
        m_opacity = 1;
    } else if (opacity < 0) {
        m_opacity = 0;
    } else {
        m_opacity = opacity;
    }

    int opacityValue = m_opacity * 255; //css accepts values 0..255
    // setStyleSheet(
    //     QString("SplashScreen{ background-color: rgba(0, 0, 0, %1); }").arg(opacityValue));

    QPixmap resultImage = QPixmap::fromImage(m_image);
    QPixmap sourceImage = QPixmap::fromImage(m_image);

    QPainter painter(&resultImage);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(resultImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawPixmap(0, 0, sourceImage);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    painter.fillRect(resultImage.rect(), QColor(43, 87, 154, opacityValue));
    painter.end();

    this->setPixmap(resultImage);
}

void SplashScreen::pluginLoaded(const QString &pluginName, bool success, const QString &errMsg)
{
    if (m_msg.count() >= MSG_MAX_LINE) {
        m_msg.pop_front();
    }

    m_msg.append(
        tr("Loaded Plugin: %1\t\t%2").arg(pluginName).arg(success ? tr("[OK]") : tr("[FAILED]\n\t> %1").arg(errMsg)));
    showMessage(m_msg.join("\n"), Qt::AlignLeft | Qt::AlignTop, m_fontColor);
    m_app->processEvents();

    int value = m_progressBar->value() + 1;
    setProgressValue(value);
}

void SplashScreen::pluginInitialized(const QString &pluginName, bool success, const QString &errMsg)
{
    if (m_msg.count() >= MSG_MAX_LINE) {
        m_msg.pop_front();
    }

    m_msg.append(tr("Initialized Plugin: %1\t\t%2")
                     .arg(pluginName)
                     .arg(success ? tr("[OK]") : tr("[FAILED]\n\t> %1").arg(errMsg)));
    showMessage(m_msg.join("\n"), Qt::AlignLeft | Qt::AlignTop, m_fontColor);
    m_app->processEvents();

    int value = m_progressBar->value() + 1;
    setProgressValue(value);
}

void SplashScreen::pluginExtensionsInitialized(const QString &pluginName, bool success, const QString &errMsg)
{
    if (m_msg.count() >= MSG_MAX_LINE) {
        m_msg.pop_front();
    }

    m_msg.append(tr("%1 Extensions Initialized : \t\t%2")
                     .arg(pluginName)
                     .arg(success ? tr("[OK]") : tr("[FAILED]\n\t> %1").arg(errMsg)));
    showMessage(m_msg.join("\n"), Qt::AlignLeft | Qt::AlignTop, m_fontColor);
    m_app->processEvents();

    int value = m_progressBar->value() + 1;
    setProgressValue(value);
}

void SplashScreen::pluginDelayedInitialized(const QString &pluginName, bool delay, const QString &errMsg)
{
    if (delay) {

        if (m_msg.count() >= MSG_MAX_LINE) {
            m_msg.pop_front();
        }

        m_msg.append(tr("%1 Delayed Initialized: \t\t%2")
                         .arg(pluginName)
                         .arg(delay ? tr("[OK]") : tr("[FAILED]\n\t> %1").arg(errMsg)));
        showMessage(m_msg.join("\n"), Qt::AlignLeft | Qt::AlignTop, m_fontColor);
    }
    m_app->processEvents();

    int value = m_progressBar->value() + 1;
    setProgressValue(value);
}

void SplashScreen::drawContents(QPainter *painter)
{
    painter->setOpacity(m_opacity);

    QSplashScreen::drawContents(painter);

    int startX = 25;
    int startY = 30;
    int width = qBound(
        0, qRound(double(m_progressBar->value() + 1) / m_progressBar->maximum() * (rect().width() - 2 * startX)),
        rect().width() - 2 * startX);

    painter->setPen(Qt::gray);
    painter->setBrush(QBrush(Qt::gray));
    painter->drawRoundedRect(QRect(startX, rect().height() - startY, rect().width() - 2 * startX, PROGRESSBAR_HEIGHT),
                             3, 3);
    painter->setPen(m_progressColor);
    painter->setBrush(QBrush(m_progressColor));
    painter->drawRoundedRect(QRect(startX, rect().height() - startY, width, PROGRESSBAR_HEIGHT), 3, 3);
}

void SplashScreen::initStyle()
{
    QString splshConfigFile = QCoreApplication::applicationDirPath() + QString("/configs/config.ini");
    QSettings config(splshConfigFile, QSettings::IniFormat);
    config.setIniCodec("UTF-8");
    QString splashPicName = config.value("SplashScreen/background").toString().trimmed();
    QString splashFilePath = qApp->applicationDirPath() + "/splash/" + splashPicName;
    if (splashPicName.isEmpty() || !QFile::exists(splashFilePath)) {
        m_image = QImage(SPLASH_BGIMAGE_WIDTH, SPLASH_BGIMAGE_HEIGHT, QImage::Format_ARGB32_Premultiplied);
        m_image.fill(qRgba(43, 87, 154, 255));
    } else {
        m_image = QImage(splashFilePath);
        // m_image = m_image.scaled(SPLASH_BGIMAGE_WIDTH, SPLASH_BGIMAGE_HEIGHT, Qt::IgnoreAspectRatio,
        //                          Qt::SmoothTransformation);
    }
    setPixmap(QPixmap::fromImage(m_image));

    QString m_progressColorName = config.value("SplashScreen/progressColor", "green").toString().trimmed();
    m_progressColor.setNamedColor(m_progressColorName);
    if (!m_progressColor.isValid()) {
        m_progressColor.setNamedColor("green");
    }

    QString m_fontColorName = config.value("SplashScreen/fontColor", "white").toString().trimmed();
    m_fontColor.setNamedColor(m_fontColorName);
    if (!m_fontColor.isValid()) {
        m_fontColor.setNamedColor("white");
    }

    // 设置进度条的位置
    m_progressBar->setAlignment(Qt::AlignCenter | Qt::AlignTop);
    m_progressBar->setGeometry(0, this->rect().height() - PROGRESSBAR_HEIGHT - 10, this->rect().width(),
                               PROGRESSBAR_HEIGHT);
    m_progressBar->setTextVisible(false);
    m_progressBar->setVisible(false);

    repaint();
}
