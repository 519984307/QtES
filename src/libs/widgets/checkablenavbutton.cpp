#include "checkablenavbutton.h"

#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QStyle>
#include <QStyleOptionButton>

CheckableNavButton::CheckableNavButton(QWidget *parent) : QPushButton(parent)
{
    paddingLeft = 20;
    paddingRight = 5;
    paddingTop = 5;
    paddingBottom = 5;
    textAlign = TextAlign_Left;

    showTriangle = false;
    triangleLen = 5;
    trianglePosition = TrianglePosition_Right;
    triangleColor = QColor(255, 255, 255);

    showIcon = false;
    iconSpace = 10;
    iconSize = QSize(16, 16);
    iconNormal = QPixmap();
    iconHover = QPixmap();
    iconCheck = QPixmap();

    showLine = true;
    lineSpace = 0;
    lineWidth = 5;
    linePosition = LinePosition_Left;
    lineColor = QColor(0, 187, 158);

    normalBgColor = QColor(230, 230, 230);
    hoverBgColor = QColor(130, 130, 130);
    checkBgColor = QColor(80, 80, 80);
    normalTextColor = QColor(100, 100, 100);
    hoverTextColor = QColor(255, 255, 255);
    checkTextColor = QColor(255, 255, 255);

    normalBgBrush = Qt::NoBrush;
    hoverBgBrush = Qt::NoBrush;
    checkBgBrush = Qt::NoBrush;

    hover = false;
    setCheckable(true);
    setText("Navigation Button");
}

void CheckableNavButton::mousePressEvent(QMouseEvent *event)
{
    this->QPushButton::mousePressEvent(event);
    if (event->isAccepted()) {
        return;
    }
    if (this->iconRect().contains(event->pos()) && (this->checkBoxUserCheckable())) {
        Qt::CheckState newCheckState;
        switch (this->checkState()) {
        case Qt::Unchecked:
        case Qt::PartiallyChecked:
            newCheckState = Qt::Checked;
            break;
        default:
        case Qt::Checked:
            newCheckState = Qt::Unchecked;
            break;
        }
        this->setCheckState(newCheckState);
        event->accept();
    }
}

bool CheckableNavButton::hitButton(const QPoint &pos) const
{
    return !this->iconRect().contains(pos) && this->QPushButton::hitButton(pos);
}

void CheckableNavButton::checkStateSet()
{
    QPushButton::checkStateSet();
    if (this->CheckBoxControlsButtonToggleState) {
        // Uncheck the checkbox if button is untoggled
        if (!this->isChecked() && this->checkState()) {
            this->setCheckState(Qt::Unchecked);
        }
    }
}

void CheckableNavButton::nextCheckState()
{
    QPushButton::nextCheckState();
    if (this->checkBoxControlsButtonToggleState()) {
        // Uncheck the checkbox if button is untoggled
        if (!this->isChecked() && this->checkState() == Qt::Checked) {
            this->setCheckState(Qt::Unchecked);
        }
    }
}

void CheckableNavButton::enterEvent(QEvent *)
{
    hover = true;
    this->update();
}

void CheckableNavButton::leaveEvent(QEvent *)
{
    hover = false;
    this->update();
}

void CheckableNavButton::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::HighQualityAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制文字
    drawText(&painter);
    //绘制图标
    drawIcon(&painter);
    //绘制边框线条
    drawLine(&painter);
    //绘制倒三角
    drawTriangle(&painter);
    //绘制CheckBox
    drawCheckBox(&painter);
}

void CheckableNavButton::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    int width = this->width();
    int height = this->height();

    QRect bgRect;
    if (linePosition == LinePosition_Left) {
        bgRect = QRect(lineSpace, 0, width - lineSpace, height);
    } else if (linePosition == LinePosition_Right) {
        bgRect = QRect(0, 0, width - lineSpace, height);
    } else if (linePosition == LinePosition_Top) {
        bgRect = QRect(0, lineSpace, width, height - lineSpace);
    } else if (linePosition == LinePosition_Bottom) {
        bgRect = QRect(0, 0, width, height - lineSpace);
    }

    //如果画刷存在则取画刷
    QBrush bgBrush;
    if (isChecked()) {
        bgBrush = checkBgBrush;
    } else if (hover) {
        bgBrush = hoverBgBrush;
    } else {
        bgBrush = normalBgBrush;
    }

    if (bgBrush != Qt::NoBrush) {
        painter->setBrush(bgBrush);
    } else {
        //根据当前状态选择对应颜色
        QColor bgColor;
        if (isChecked()) {
            bgColor = checkBgColor;
        } else if (hover) {
            bgColor = hoverBgColor;
        } else {
            bgColor = normalBgColor;
        }

        painter->setBrush(bgColor);
    }

    painter->drawRect(bgRect);

    painter->restore();
}

void CheckableNavButton::drawText(QPainter *painter)
{
    painter->save();
    painter->setBrush(Qt::NoBrush);

    //根据当前状态选择对应颜色
    QColor textColor;
    if (isChecked()) {
        textColor = checkTextColor;
    } else if (hover) {
        textColor = hoverTextColor;
    } else {
        textColor = normalTextColor;
    }

    QRect textRect
        = QRect(paddingLeft, paddingTop, width() - paddingLeft - paddingRight, height() - paddingTop - paddingBottom);
    painter->setPen(textColor);
    painter->drawText(textRect, textAlign | Qt::AlignVCenter, text());

    painter->restore();
}

void CheckableNavButton::drawIcon(QPainter *painter)
{
    if (!showIcon) {
        return;
    }

    painter->save();

    QPixmap pix;
    if (isChecked()) {
        pix = iconCheck;
    } else if (hover) {
        pix = iconHover;
    } else {
        pix = iconNormal;
    }

    if (!pix.isNull()) {
        //等比例平滑缩放图标
        pix = pix.scaled(iconSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        painter->drawPixmap(iconSpace, (height() - iconSize.height()) / 2, pix);
    }

    painter->restore();
}

void CheckableNavButton::drawLine(QPainter *painter)
{
    if (!showLine) {
        return;
    }

    if (!isChecked()) {
        return;
    }

    painter->save();

    QPen pen;
    pen.setWidth(lineWidth);
    pen.setColor(lineColor);
    painter->setPen(pen);

    //根据线条位置设置线条坐标
    QPoint pointStart, pointEnd;
    if (linePosition == CheckableNavButton::LinePosition_Left) {
        pointStart = QPoint(0, 0);
        pointEnd = QPoint(0, height());
    } else if (linePosition == CheckableNavButton::LinePosition_Right) {
        pointStart = QPoint(width(), 0);
        pointEnd = QPoint(width(), height());
    } else if (linePosition == CheckableNavButton::LinePosition_Top) {
        pointStart = QPoint(0, 0);
        pointEnd = QPoint(width(), 0);
    } else if (linePosition == CheckableNavButton::LinePosition_Bottom) {
        pointStart = QPoint(0, height());
        pointEnd = QPoint(width(), height());
    }

    painter->drawLine(pointStart, pointEnd);

    painter->restore();
}

void CheckableNavButton::drawTriangle(QPainter *painter)
{
    if (!showTriangle) {
        return;
    }

    //选中或者悬停显示
    if (!hover && !isChecked()) {
        return;
    }

    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(triangleColor);

    //绘制在右侧中间,根据设定的倒三角的边长设定三个点位置
    int width = this->width();
    int height = this->height();
    int midWidth = width / 2;
    int midHeight = height / 2;

    QPolygon pts;
    if (trianglePosition == TrianglePosition_Left) {
        pts.setPoints(3, triangleLen, midHeight, 0, midHeight - triangleLen, 0, midHeight + triangleLen);
    } else if (trianglePosition == TrianglePosition_Right) {
        pts.setPoints(3, width - triangleLen, midHeight, width, midHeight - triangleLen, width,
                      midHeight + triangleLen);
    } else if (trianglePosition == TrianglePosition_Top) {
        pts.setPoints(3, midWidth, triangleLen, midWidth - triangleLen, 0, midWidth + triangleLen, 0);
    } else if (trianglePosition == TrianglePosition_Bottom) {
        pts.setPoints(3, midWidth, height - triangleLen, midWidth - triangleLen, height, midWidth + triangleLen,
                      height);
    }

    painter->drawPolygon(pts);

    painter->restore();
}

void CheckableNavButton::drawCheckBox(QPainter *painter)
{
    QStyleOptionButton indicatorOpt;
    indicatorOpt.init(this);
    indicatorOpt.rect = iconRect();

    if (!this->checkBoxUserCheckable()) {
        indicatorOpt.state &= ~QStyle::State_Enabled;
    }
    if (this->checkBoxControlsButton()) {
        // Hack: calling setCheckable() instead of setCheckState while being in a
        // control button mode leads to an inconsistent state, we need to make
        // synchronize the 2 properties.
        this->setCheckState(this->isCheckable() ? Qt::Checked : Qt::Unchecked);
    }
    switch (this->checkState()) {
    case Qt::Checked:
        indicatorOpt.state |= QStyle::State_On;
        break;
    case Qt::PartiallyChecked:
        indicatorOpt.state |= QStyle::State_NoChange;
        break;
    default:
    case Qt::Unchecked:
        indicatorOpt.state |= QStyle::State_Off;
        break;
    }

    this->style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &indicatorOpt, painter, 0);
}

int CheckableNavButton::getPaddingLeft() const
{
    return this->paddingLeft;
}

int CheckableNavButton::getPaddingRight() const
{
    return this->paddingRight;
}

int CheckableNavButton::getPaddingTop() const
{
    return this->paddingTop;
}

int CheckableNavButton::getPaddingBottom() const
{
    return this->paddingBottom;
}

CheckableNavButton::TextAlign CheckableNavButton::getTextAlign() const
{
    return this->textAlign;
}

bool CheckableNavButton::getShowTriangle() const
{
    return this->showTriangle;
}

int CheckableNavButton::getTriangleLen() const
{
    return this->triangleLen;
}

CheckableNavButton::TrianglePosition CheckableNavButton::getTrianglePosition() const
{
    return this->trianglePosition;
}

QColor CheckableNavButton::getTriangleColor() const
{
    return this->triangleColor;
}

bool CheckableNavButton::getShowIcon() const
{
    return this->showIcon;
}

int CheckableNavButton::getIconSpace() const
{
    return this->iconSpace;
}

QSize CheckableNavButton::getIconSize() const
{
    return this->iconSize;
}

QRect CheckableNavButton::iconRect() const
{
    return QRect(QPoint(iconSpace, (height() - iconSize.height()) / 2), this->iconSize);
}

QPixmap CheckableNavButton::getIconNormal() const
{
    return this->iconNormal;
}

QPixmap CheckableNavButton::getIconHover() const
{
    return this->iconHover;
}

QPixmap CheckableNavButton::getIconCheck() const
{
    return this->iconCheck;
}

bool CheckableNavButton::getShowLine() const
{
    return this->showLine;
}

int CheckableNavButton::getLineSpace() const
{
    return this->lineSpace;
}

int CheckableNavButton::getLineWidth() const
{
    return this->lineWidth;
}

CheckableNavButton::LinePosition CheckableNavButton::getLinePosition() const
{
    return this->linePosition;
}

QColor CheckableNavButton::getLineColor() const
{
    return this->lineColor;
}

QColor CheckableNavButton::getNormalBgColor() const
{
    return this->normalBgColor;
}

QColor CheckableNavButton::getHoverBgColor() const
{
    return this->hoverBgColor;
}

QColor CheckableNavButton::getCheckBgColor() const
{
    return this->checkBgColor;
}

QColor CheckableNavButton::getNormalTextColor() const
{
    return this->normalTextColor;
}

QColor CheckableNavButton::getHoverTextColor() const
{
    return this->hoverTextColor;
}

QColor CheckableNavButton::getCheckTextColor() const
{
    return this->checkTextColor;
}

bool CheckableNavButton::checkBoxControlsButton() const
{
    return this->CheckBoxControlsButton;
}

void CheckableNavButton::setCheckBoxControlsButton(bool b)
{
    this->CheckBoxControlsButton = b;
    if (b) {
        // synchronize checkstate with the checkable property.
        this->setCheckState(this->isCheckable() ? Qt::Checked : Qt::Unchecked);
    }
    this->update();
}

bool CheckableNavButton::checkBoxControlsButtonToggleState() const
{
    return this->CheckBoxControlsButtonToggleState;
}

void CheckableNavButton::setCheckBoxControlsButtonToggleState(bool b)
{
    if (this->CheckBoxControlsButtonToggleState == b) {
        return;
    }
    this->CheckBoxControlsButtonToggleState = b;
    if (this->CheckBoxControlsButtonToggleState) {
        // We have just enabled sync between toggle state and checkbox.
        // If checkbox is enabled then make the button toggled.
        if (this->checkState() && !this->isChecked()) {
            this->setChecked(true);
        }
    }
    this->update();
}

bool CheckableNavButton::checkBoxUserCheckable() const
{
    return this->CheckBoxUserCheckable;
}

void CheckableNavButton::setCheckBoxUserCheckable(bool b)
{
    this->CheckBoxUserCheckable = b;
    this->update();
}

Qt::CheckState CheckableNavButton::checkState() const
{
    return this->CheckState;
}

void CheckableNavButton::setCheckState(Qt::CheckState checkState)
{
    Qt::CheckState oldCheckState = this->CheckState;
    if (checkState == oldCheckState) {
        return;
    }
    this->CheckState = checkState;
    if (this->checkBoxControlsButton()) {
        bool wasChecked = this->isChecked();
        this->setCheckable(checkState == Qt::Checked);
        // QCheckBox::setCheckable() doesn't emit toggled signal
        if (wasChecked != this->isChecked()) {
            emit toggled(this->isChecked());
        }
        if (this->checkBoxControlsButtonToggleState()) {
            if (this->isChecked() != (checkState == Qt::Checked)) {
                this->setChecked(checkState == Qt::Checked);
            }
        }
    }
    emit checkStateChanged(this->CheckState);
    emit checkBoxToggled(this->CheckState == Qt::Checked);
    qDebug() << this->CheckState;
    this->update();
}

void CheckableNavButton::setPaddingLeft(int paddingLeft)
{
    if (this->paddingLeft != paddingLeft) {
        this->paddingLeft = paddingLeft;
        this->update();
    }
}

void CheckableNavButton::setPaddingRight(int paddingRight)
{
    if (this->paddingRight != paddingRight) {
        this->paddingRight = paddingRight;
        this->update();
    }
}

void CheckableNavButton::setPaddingTop(int paddingTop)
{
    if (this->paddingTop != paddingTop) {
        this->paddingTop = paddingTop;
        this->update();
    }
}

void CheckableNavButton::setPaddingBottom(int paddingBottom)
{
    if (this->paddingBottom != paddingBottom) {
        this->paddingBottom = paddingBottom;
        this->update();
    }
}

void CheckableNavButton::setPadding(int padding)
{
    setPadding(padding, padding, padding, padding);
}

void CheckableNavButton::setPadding(int paddingLeft, int paddingRight, int paddingTop, int paddingBottom)
{
    this->paddingLeft = paddingLeft;
    this->paddingRight = paddingRight;
    this->paddingTop = paddingTop;
    this->paddingBottom = paddingBottom;
    this->update();
}

void CheckableNavButton::setTextAlign(const CheckableNavButton::TextAlign &textAlign)
{
    if (this->textAlign != textAlign) {
        this->textAlign = textAlign;
        this->update();
    }
}

void CheckableNavButton::setShowTriangle(bool showTriangle)
{
    if (this->showTriangle != showTriangle) {
        this->showTriangle = showTriangle;
        this->update();
    }
}

void CheckableNavButton::setTriangleLen(int triangleLen)
{
    if (this->triangleLen != triangleLen) {
        this->triangleLen = triangleLen;
        this->update();
    }
}

void CheckableNavButton::setTrianglePosition(const CheckableNavButton::TrianglePosition &trianglePosition)
{
    if (this->trianglePosition != trianglePosition) {
        this->trianglePosition = trianglePosition;
        this->update();
    }
}

void CheckableNavButton::setTriangleColor(const QColor &triangleColor)
{
    if (this->triangleColor != triangleColor) {
        this->triangleColor = triangleColor;
        this->update();
    }
}

void CheckableNavButton::setShowIcon(bool showIcon)
{
    if (this->showIcon != showIcon) {
        this->showIcon = showIcon;
        this->update();
    }
}

void CheckableNavButton::setIconSpace(int iconSpace)
{
    if (this->iconSpace != iconSpace) {
        this->iconSpace = iconSpace;
        this->update();
    }
}

void CheckableNavButton::setIconSize(const QSize &iconSize)
{
    if (this->iconSize != iconSize) {
        this->iconSize = iconSize;
        this->update();
    }
}

void CheckableNavButton::setIconNormal(const QPixmap &iconNormal)
{
    this->iconNormal = iconNormal;
    this->update();
}

void CheckableNavButton::setIconHover(const QPixmap &iconHover)
{
    this->iconHover = iconHover;
    this->update();
}

void CheckableNavButton::setIconCheck(const QPixmap &iconCheck)
{
    this->iconCheck = iconCheck;
    this->update();
}

void CheckableNavButton::setShowLine(bool showLine)
{
    if (this->showLine != showLine) {
        this->showLine = showLine;
        this->update();
    }
}

void CheckableNavButton::setLineSpace(int lineSpace)
{
    if (this->lineSpace != lineSpace) {
        this->lineSpace = lineSpace;
        this->update();
    }
}

void CheckableNavButton::setLineWidth(int lineWidth)
{
    if (this->lineWidth != lineWidth) {
        this->lineWidth = lineWidth;
        this->update();
    }
}

void CheckableNavButton::setLinePosition(const CheckableNavButton::LinePosition &linePosition)
{
    if (this->linePosition != linePosition) {
        this->linePosition = linePosition;
        this->update();
    }
}

void CheckableNavButton::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        this->update();
    }
}

void CheckableNavButton::setNormalBgColor(const QColor &normalBgColor)
{
    if (this->normalBgColor != normalBgColor) {
        this->normalBgColor = normalBgColor;
        this->update();
    }
}

void CheckableNavButton::setHoverBgColor(const QColor &hoverBgColor)
{
    if (this->hoverBgColor != hoverBgColor) {
        this->hoverBgColor = hoverBgColor;
        this->update();
    }
}

void CheckableNavButton::setCheckBgColor(const QColor &checkBgColor)
{
    if (this->checkBgColor != checkBgColor) {
        this->checkBgColor = checkBgColor;
        this->update();
    }
}

void CheckableNavButton::setNormalTextColor(const QColor &normalTextColor)
{
    if (this->normalTextColor != normalTextColor) {
        this->normalTextColor = normalTextColor;
        this->update();
    }
}

void CheckableNavButton::setHoverTextColor(const QColor &hoverTextColor)
{
    if (this->hoverTextColor != hoverTextColor) {
        this->hoverTextColor = hoverTextColor;
        this->update();
    }
}

void CheckableNavButton::setCheckTextColor(const QColor &checkTextColor)
{
    if (this->checkTextColor != checkTextColor) {
        this->checkTextColor = checkTextColor;
        this->update();
    }
}

void CheckableNavButton::setNormalBgBrush(const QBrush &normalBgBrush)
{
    if (this->normalBgBrush != normalBgBrush) {
        this->normalBgBrush = normalBgBrush;
        this->update();
    }
}

void CheckableNavButton::setHoverBgBrush(const QBrush &hoverBgBrush)
{
    if (this->hoverBgBrush != hoverBgBrush) {
        this->hoverBgBrush = hoverBgBrush;
        this->update();
    }
}

void CheckableNavButton::setCheckBgBrush(const QBrush &checkBgBrush)
{
    if (this->checkBgBrush != checkBgBrush) {
        this->checkBgBrush = checkBgBrush;
        this->update();
    }
}
