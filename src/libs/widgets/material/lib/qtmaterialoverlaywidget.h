#ifndef QTMATERIALOVERLAYWIDGET_H
#define QTMATERIALOVERLAYWIDGET_H

#include <QWidget>

class QtMaterialOverlayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QtMaterialOverlayWidget(QWidget *parent = 0);
    ~QtMaterialOverlayWidget();

protected:
    bool event(QEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

    virtual QRect overlayGeometry() const;

private:
    Q_DISABLE_COPY(QtMaterialOverlayWidget)
};

#endif // QTMATERIALOVERLAYWIDGET_H
