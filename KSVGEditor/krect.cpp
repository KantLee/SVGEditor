#include "krect.h"

KRect::KRect(QObject *parent)
	: KShape(parent)
{
}

KRect::~KRect()
{
}

// 绘制正方形
void KRect::drawShape(QPaintDevice *parent)
{
    QPainter painter(parent);
    // 开启防锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    // 应用缩放变换
    QTransform transform;
    qreal scaleFactor = getShapeScale();
    transform.scale(scaleFactor, scaleFactor);
    painter.setTransform(transform);
    // 获取边框宽度、样式、颜色和填充颜色
    qreal width = qreal(getBorderWidth());
    Qt::PenStyle borderStyle = getBorderStyle();
    QRgb borderColor = getBorderColor();
    QRgb shapeColor = getShapeColor();
    // 设置画笔
    painter.setPen(QPen(QColor(borderColor),width,borderStyle));
    painter.setBrush(QBrush(QColor(getShapeColor())));
    painter.drawRect(getShapeRect());
}

KShapeType KRect::getShapeType()
{
    return KShapeType::RectShapeType;
}
