#include "khexagon.h"

KHexagon::KHexagon(QObject *parent)
	: KShape(parent)
{
}

KHexagon::~KHexagon()
{
}

void KHexagon::drawShape(QPaintDevice *parent)
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
    qreal borderWidth = qreal(getBorderWidth());
    Qt::PenStyle borderStyle = getBorderStyle();
    QColor borderColor = QColor(getBorderColor());
    QColor shapeColor = QColor(getShapeColor());

    // 设置画笔
    painter.setPen(QPen(borderColor, borderWidth, borderStyle));
    painter.setBrush(QBrush(shapeColor));

    QRectF shapeRect = getShapeRect();
    int rectWidth = shapeRect.width();
    int rectHeight = shapeRect.height();
    // 确定六边形的六个顶点，从左上角开始顺时针进行
    QPointF points[6];
    points[0].setX(shapeRect.x() + rectWidth * 1.0 / 4.0);
    points[0].setY(shapeRect.y());
	points[1].setX(shapeRect.x() + rectWidth * 3.0 / 4.0);
	points[1].setY(shapeRect.y());
    points[2].setX(shapeRect.right());
    points[2].setY(shapeRect.y() + rectHeight * 1.0 / 2.0);
	points[3].setX(shapeRect.x() + rectWidth * 3.0 / 4.0);
    points[3].setY(shapeRect.bottom());
	points[4].setX(shapeRect.x() + rectWidth * 1.0 / 4.0);
	points[4].setY(shapeRect.bottom());
    points[5].setX(shapeRect.x());
    points[5].setY(shapeRect.y() + rectHeight * 1.0 / 2.0);
    // 绘制
    painter.drawPolygon(points, 6);
}

KShapeType KHexagon::getShapeType()
{
    return KShapeType::HexagonShapeType;
}
