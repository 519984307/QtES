#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QProgressBar>
#include <QSplashScreen>

class SplashScreen : public QSplashScreen
{
    Q_OBJECT
    Q_PROPERTY(float opacity READ opacity WRITE setOpacity)

public:
    explicit SplashScreen(QApplication *app, QWidget *parent = 0);
    ~SplashScreen();

    void setProgressRange(int min, int max);
    void setProgressValue(int value);

    void finish(QWidget *w);

    float opacity() const;
    void setOpacity(const float opacity);

public slots:
    void pluginLoaded(const QString &pluginName, bool success, const QString &errMsg);
    void pluginInitialized(const QString &pluginName, bool success, const QString &errMsg);
    void pluginExtensionsInitialized(const QString &pluginName, bool success, const QString &errMsg);
    void pluginDelayedInitialized(const QString &pluginName, bool delay, const QString &errMsg);

protected:
    void drawContents(QPainter *painter) override;
    void mousePressEvent(QMouseEvent *) override {}

private:
    void initStyle();

protected:
    QApplication *m_app;
    QProgressBar *m_progressBar;
    QStringList m_msg;
    QColor m_progressColor;
    QColor m_fontColor;
    float m_opacity;
    QImage m_image;

    enum
    {
        SPLASH_BGIMAGE_WIDTH = 650,
        SPLASH_BGIMAGE_HEIGHT = 400,
        PROGRESSBAR_HEIGHT = 8,
        MSG_MAX_LINE = 4
    };
};

#endif // SPLASHSCREEN_H
