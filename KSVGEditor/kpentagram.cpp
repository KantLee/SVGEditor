#include "kpentagram.h"

KPentagram::KPentagram(QObject *parent)
	: KShape(parent)
{
}

KPentagram::~KPentagram()
{
}

void KPentagram::drawShape(QPaintDevice *parent)
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
    QColor borderColor = QColor(getBorderColor());
    QColor shapeColor = QColor(getShapeColor());

    // 设置画笔
    painter.setPen(QPen(borderColor, width, borderStyle));
    painter.setBrush(QBrush(shapeColor));

    QRectF shapeRect = getShapeRect();
    qreal centerX = shapeRect.center().x();
    qreal centerY = shapeRect.center().y();
    qreal outerRadius = qMin(shapeRect.width(), shapeRect.height()) / 2.0;
    qreal innerRadius = outerRadius / 2.5;

    // 确定五角星的顶点
    QPointF points[10];
    for (int i = 0; i < 10; ++i) 
    {
        double angle = M_PI / 5.0 * i; // 36度
        qreal radius = (i % 2 == 0) ? outerRadius : innerRadius;
        points[i] = QPointF(centerX + radius * cos(angle - M_PI / 2.0),
            centerY + radius * sin(angle - M_PI / 2.0));
    }

    painter.drawPolygon(points, 10);
}

KShapeType KPentagram::getShapeType()
{
    return KShapeType::PentagramShapeType;
}
