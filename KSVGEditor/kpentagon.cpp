#include "kpentagon.h"

KPentagon::KPentagon(QObject *parent)
	: KShape(parent)
{
}

KPentagon::~KPentagon()
{
}

void KPentagon::drawShape(QPaintDevice *parent)
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
    painter.setPen(QPen(QColor(borderColor), width, borderStyle));
    painter.setBrush(QBrush(QColor(getShapeColor())));
    // 获取边界矩形的顶点坐标
    QRectF shapeRect = getShapeRect();
    int rectWidth = shapeRect.width();
    int rectHeight = shapeRect.height();
    // 确定五边形的五个顶点，从最上方的顶点开始顺时针进行
	QPointF points[5];
    points[0] = QPointF(shapeRect.x() + rectWidth / 2.0, shapeRect.y());
    points[1] = QPointF(shapeRect.right(), shapeRect.y() + rectHeight / 2.0);
    points[2] = QPointF(shapeRect.x() + rectWidth * 3.0 / 4.0, shapeRect.bottom());
    points[3] = QPointF(shapeRect.x() + rectWidth / 4.0, shapeRect.bottom());
    points[4] = QPointF(shapeRect.x(), shapeRect.y() + rectHeight / 2.0);
    // 绘制
    painter.drawPolygon(points,5);
}

KShapeType KPentagon::getShapeType()
{
    return KShapeType::PentagonShapeType;
}
