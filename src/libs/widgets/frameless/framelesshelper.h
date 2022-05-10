#ifndef FRAMELESSHELPERS_H
#define FRAMELESSHELPERS_H

#include <QBitmap>
#include <QPainter>
#include <QtGui>

namespace Widgets {

class Frame;
class WidgetData;

/*****
 * FramelessHelperPrivate
 * Data collection saves the movable and scalable attributes
 *****/
class FramelessHelperPrivate
{
public:
    QHash<QWidget *, WidgetData *> m_widgetDataHash;
    bool m_bWidgetMovable : true;
    bool m_bWidgetResizable : true;
    bool m_bRubberBandOnResize : true;
    bool m_bRubberBandOnMove : true;
};

/*****
 * CursorPosCalculator
 * calculate whether the mouse locates at left, top, right, botton, top-left, bottom-left, top-right
 *and bottom-right corners.
 *****/
class CursorPosCalculator
{
public:
    explicit CursorPosCalculator();
    void reset();
    void recalculate(const QPoint &globalMousePos, const QRect &frameRect);

public:
    bool m_bOnEdges : true;
    bool m_bOnLeftEdge : true;
    bool m_bOnRightEdge : true;
    bool m_bOnTopEdge : true;
    bool m_bOnBottomEdge : true;
    bool m_bOnTopLeftEdge : true;
    bool m_bOnBottomLeftEdge : true;
    bool m_bOnTopRightEdge : true;
    bool m_bOnBottomRightEdge : true;

    static int m_nBorderWidth;
    static int m_nTitleHeight;
};

/*****
 * WidgetData
 * handle the update event such as update the mouse style, move and scale the frame.
 *****/
class WidgetData
{
public:
    explicit WidgetData(FramelessHelperPrivate *d, QWidget *pTopLevelWidget);
    ~WidgetData();
    QWidget *widget();

    void handleWidgetEvent(QEvent *event);

    void updateRubberBandStatus();

private:
    void updateCursorShape(const QPoint &gMousePos);

    void resizeWidget(const QPoint &gMousePos);

    void moveWidget(const QPoint &gMousePos);

    void handleMousePressEvent(QMouseEvent *event);

    void handleMouseReleaseEvent(QMouseEvent *event);

    void handleMouseMoveEvent(QMouseEvent *event);

    void handleLeaveEvent(QEvent *event);

    void handleHoverMoveEvent(QHoverEvent *event);

private:
    FramelessHelperPrivate *d;
    QWidget *m_pWidget;
    QPoint m_ptDragPos;
    CursorPosCalculator m_pressedMousePos;
    CursorPosCalculator m_moveMousePos;
    bool m_bLeftButtonPressed;
    bool m_bCursorShapeChanged;
    bool m_bLeftButtonTitlePressed;
    Qt::WindowFlags m_windowFlags;
};

class FramelessHelper : public QObject
{
    Q_OBJECT

public:
    explicit FramelessHelper(QObject *parent = 0);
    ~FramelessHelper();

    void activateOn(QWidget *topLevelWidget);

    void removeFrom(QWidget *topLevelWidget);

    void setWidgetMovable(bool movable);

    void setWidgetResizable(bool resizable);

    void setRubberBandOnMove(bool movable);

    void setRubberBandOnResize(bool resizable);

    void setBorderWidth(uint width);

    void setTitleHeight(uint height);
    bool widgetResizable();
    bool widgetMovable();
    bool rubberBandOnMove();
    bool rubberBandOnResisze();
    uint borderWidth();
    uint titleHeight();

signals:
    void signalDoubleClick();

protected:
    virtual bool eventFilter(QObject *obj, QEvent *event);

private:
    FramelessHelperPrivate *d;
};
} // namespace Widgets

#endif // FRAMELESSHELPERS_H
