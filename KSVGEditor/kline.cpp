#include "kline.h"

KLine::KLine(QObject *parent)
	: KShape(parent)
{
}

KLine::~KLine()
{
}

void KLine::drawShape(QPaintDevice *parent)
{
    QPainter painter(parent);
    // 开启防锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    // 应用缩放变换
    QTransform transform;
    qreal scaleFactor = getShapeScale();
    transform.scale(scaleFactor, scaleFactor);
    painter.setTransform(transform);
    // 获取边框宽度、样式、颜色
    qreal width = qreal(getBorderWidth());
    Qt::PenStyle borderStyle = getBorderStyle();
    QRgb borderColor = getBorderColor();
    // 设置画笔
    painter.setPen(QPen(QColor(borderColor), width, borderStyle));
    painter.drawLine(getShapeRect().topLeft(), getShapeRect().bottomRight());
}

KShapeType KLine::getShapeType()
{
    return KShapeType::LineShapeType;
}
