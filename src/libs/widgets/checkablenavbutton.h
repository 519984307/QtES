#ifndef CHECKABLENAVBUTTON_H
#define CHECKABLENAVBUTTON_H

#include <QPushButton>

#include "widgets_global.h"

class WIDGETS_EXPORT CheckableNavButton : public QPushButton
{
    Q_OBJECT
    Q_ENUMS(TextAlign)
    Q_ENUMS(TrianglePosition)
    Q_ENUMS(LinePosition)
    Q_ENUMS(IconPosition)

public:
    enum TextAlign
    {
        TextAlign_Left = 0x0001,
        TextAlign_Right = 0x0002,
        TextAlign_Top = 0x0020,
        TextAlign_Bottom = 0x0040,
        TextAlign_Center = 0x0004
    };

    enum TrianglePosition
    {
        TrianglePosition_Left = 0,
        TrianglePosition_Right = 1,
        TrianglePosition_Top = 2,
        TrianglePosition_Bottom = 3
    };

    enum IconPosition
    {
        IconPosition_Left = 0,
        IconPosition_Right = 1,
        IconPosition_Top = 2,
        IconPosition_Bottom = 3
    };

    enum LinePosition
    {
        LinePosition_Left = 0,
        LinePosition_Right = 1,
        LinePosition_Top = 2,
        LinePosition_Bottom = 3
    };

    explicit CheckableNavButton(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    bool hitButton(const QPoint &pos) const override;
    void checkStateSet() override;
    void nextCheckState() override;

    void enterEvent(QEvent *) override;
    void leaveEvent(QEvent *) override;
    void paintEvent(QPaintEvent *) override;

    void drawBg(QPainter *painter);
    void drawText(QPainter *painter);
    void drawIcon(QPainter *painter);
    void drawLine(QPainter *painter);
    void drawTriangle(QPainter *painter);
    void drawCheckBox(QPainter *painter);

public:
    int getPaddingLeft() const;
    int getPaddingRight() const;
    int getPaddingTop() const;
    int getPaddingBottom() const;
    TextAlign getTextAlign() const;

    bool getShowTriangle() const;
    int getTriangleLen() const;
    TrianglePosition getTrianglePosition() const;
    QColor getTriangleColor() const;

    bool getShowIcon() const;
    int getIconSpace() const;
    QSize getIconSize() const;
    QRect iconRect() const;
    QPixmap getIconNormal() const;
    QPixmap getIconHover() const;
    QPixmap getIconCheck() const;

    bool getShowLine() const;
    int getLineSpace() const;
    int getLineWidth() const;
    LinePosition getLinePosition() const;
    QColor getLineColor() const;

    QColor getNormalBgColor() const;
    QColor getHoverBgColor() const;
    QColor getCheckBgColor() const;
    QColor getNormalTextColor() const;
    QColor getHoverTextColor() const;
    QColor getCheckTextColor() const;

public:
    /// By default the checkbox is connected to the checkable property of the push button.
    /// You can change this behaviour by clearing the "checkBoxControlsButton"
    /// property.
    /// \note In checkBoxControlsButton mode, calling setCheckable() instead of
    /// setCheckState() may not refresh the button automatically. Use setCheckState()
    /// instead.
    /// \note You can automatically check the button when the user checks the
    /// checkbox by connecting the checkBoxToggled(bool) signal with the
    /// setChecked(bool) slot or by enabling "checkBoxControlsButtonToggleState" property.
    virtual bool checkBoxControlsButton() const;
    virtual void setCheckBoxControlsButton(bool b);

    /// If both checkBoxControlsButton and checkBoxControlsButtonToggleState
    /// are enabled then check state is synchronized with pushed state of the button
    /// (checking the checkbox also pushes down the button and releasing the button
    /// unchecks the checkbox).
    virtual bool checkBoxControlsButtonToggleState() const;
    virtual void setCheckBoxControlsButtonToggleState(bool b);

    /// The checkBoxUserCheckable property determines if the state of the
    /// checkbox can be changed interactively by the user by clicking on the
    /// checkbox.
    virtual bool checkBoxUserCheckable() const;
    virtual void setCheckBoxUserCheckable(bool b);

    /// Get checked state of the checkbox on the button.
    virtual Qt::CheckState checkState() const;
    /// Set checked state of the checkbox on the button.
    virtual void setCheckState(Qt::CheckState checkState);

public Q_SLOTS:
    void setPaddingLeft(int paddingLeft);
    void setPaddingRight(int paddingRight);
    void setPaddingTop(int paddingTop);
    void setPaddingBottom(int paddingBottom);
    void setPadding(int padding);
    void setPadding(int paddingLeft, int paddingRight, int paddingTop, int paddingBottom);

    void setTextAlign(const CheckableNavButton::TextAlign &textAlign);

    void setShowTriangle(bool showTriangle);
    void setTriangleLen(int triangleLen);
    void setTrianglePosition(const CheckableNavButton::TrianglePosition &trianglePosition);
    void setTriangleColor(const QColor &triangleColor);

    void setShowIcon(bool showIcon);
    void setIconSpace(int iconSpace);
    void setIconSize(const QSize &iconSize);
    void setIconNormal(const QPixmap &iconNormal);
    void setIconHover(const QPixmap &iconHover);
    void setIconCheck(const QPixmap &iconCheck);

    void setShowLine(bool showLine);
    void setLineSpace(int lineSpace);
    void setLineWidth(int lineWidth);
    void setLinePosition(const CheckableNavButton::LinePosition &linePosition);
    void setLineColor(const QColor &lineColor);

    void setNormalBgColor(const QColor &normalBgColor);
    void setHoverBgColor(const QColor &hoverBgColor);
    void setCheckBgColor(const QColor &checkBgColor);

    void setNormalTextColor(const QColor &normalTextColor);
    void setHoverTextColor(const QColor &hoverTextColor);
    void setCheckTextColor(const QColor &checkTextColor);

    void setNormalBgBrush(const QBrush &normalBgBrush);
    void setHoverBgBrush(const QBrush &hoverBgBrush);
    void setCheckBgBrush(const QBrush &checkBgBrush);

Q_SIGNALS:
    /// Fired anytime the checkbox change of state
    void checkBoxToggled(bool);
    /// Fired anytime the checkbox change of state
    void checkStateChanged(Qt::CheckState newCheckState);

private:
    int paddingLeft;
    int paddingRight;
    int paddingTop;
    int paddingBottom;
    TextAlign textAlign;

    bool showTriangle;
    int triangleLen;
    TrianglePosition trianglePosition;
    QColor triangleColor;

    bool showIcon;
    int iconSpace;
    QSize iconSize;
    QPixmap iconNormal;
    QPixmap iconHover;
    QPixmap iconCheck;

    bool showLine;
    int lineSpace;
    int lineWidth;
    LinePosition linePosition;
    QColor lineColor;

    QColor normalBgColor;
    QColor hoverBgColor;
    QColor checkBgColor;
    QColor normalTextColor;
    QColor hoverTextColor;
    QColor checkTextColor;

    QBrush normalBgBrush;
    QBrush hoverBgBrush;
    QBrush checkBgBrush;

    bool hover;

    // checkbox
    bool CheckBoxControlsButton = true;
    bool CheckBoxUserCheckable = true;
    bool CheckBoxControlsButtonToggleState = false;
    Qt::CheckState CheckState = Qt::Unchecked;
};

#endif // CheckableNavButton_H
