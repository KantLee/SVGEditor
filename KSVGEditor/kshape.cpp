#include "kshape.h"
#include "kshapeparameter.h"

KShape::KShape(QObject *parent)
	: QObject(parent)
	, m_borderWidth(KShapeParameter::getInstance()->getBorderWidth())
	, m_borderStyle(KShapeParameter::getInstance()->getBorderStyle())
	, m_borderColor(KShapeParameter::getInstance()->getBorderColor())
	, m_shapeColor(KShapeParameter::getInstance()->getShapeColor())
	, m_scaleFactor(KShapeParameter::getInstance()->getCanvasScale())
{
}

KShape::~KShape()
{
}

// 获取起始坐标点
QPointF KShape::getStartPoint() const
{
	return m_startPoint;
}

// 获取绘画结束坐标点
QPointF KShape::getEndPoint() const
{
	return m_endPoint;
}

// 设置绘画起始坐标点
void KShape::setStartPoint(const QPointF &point)
{
	m_startPoint = point;
}

// 设置绘画结束坐标点
void KShape::setEndPoint(const QPointF &point)
{
	m_endPoint = point;
}

// 判断绘画是否合法
bool KShape::isShapeVaild() const
{
	return (m_startPoint.x() != m_endPoint.x() || m_startPoint.y() != m_endPoint.y());
}

KShapeType KShape::getShapeType()
{
	return KShapeType::None;
}

QRectF KShape::getShapeRect()
{
	return QRectF(m_startPoint, m_endPoint);
}


void KShape::drawOutline(QPaintDevice *parent)
{
	QPainter painter(parent);
	// 开启防锯齿
	painter.setRenderHint(QPainter::Antialiasing);
	// 应用缩放变换
	QTransform transform;
	transform.scale(m_scaleFactor, m_scaleFactor);
	painter.setTransform(transform);
	painter.setPen(QPen(Qt::black, 1.0, Qt::DashLine));	// 虚线
	painter.drawRect(getShapeRect());
}

// 选中图形高亮显示边框以及八个控制点
void KShape::drawSelectedHighlight(QPaintDevice *parent, bool drawControl)
{
	QPainter painter(parent);
	// 开启防锯齿
	painter.setRenderHint(QPainter::Antialiasing);
	// 应用缩放变换
	QTransform transform;
	transform.scale(m_scaleFactor, m_scaleFactor);
	painter.setTransform(transform);
	painter.setPen(QPen(QColor(128, 0, 128), 2.0, Qt::SolidLine));
	// 获取矩形框的宽和高
	int shapeWidth = m_endPoint.x() - m_startPoint.x();
	int shapeHeight = m_endPoint.y() - m_startPoint.y();
	// 如果边界矩形的宽度或高度小于等于0，则返回不进行绘制
	if (shapeWidth <= 0 || shapeHeight <= 0)
		return;
	// 绘制边界矩形
	painter.drawRect(getShapeRect());
	// 检查是否需要绘制控制点
	if (!drawControl)
		return;
	// 获取边界矩形的左上角坐标
	QPointF shapeLeftTopXY = m_startPoint;
	// 获取缩放比例
	qreal scale = KShapeParameter::getInstance()->getShapeScale();
	// 设置控制点的一半长度的值
	qreal halfLength = 4.0 * scale;
	// 遍历8个控制点，并设置它们的位置和大小
	for (int i = 0; i < 8; i++)
	{
		switch (i)
		{
		case 0:	// 设置左上角的控制点的左上角坐标
			m_controlRect[i].setX(shapeLeftTopXY.x() - halfLength);
			m_controlRect[i].setY(shapeLeftTopXY.y() - halfLength);
			break;
		case 1:	// 设置上边中点的控制点的左上角坐标
			m_controlRect[i].setX(shapeLeftTopXY.x() + shapeWidth / 2.0 - halfLength);
			m_controlRect[i].setY(shapeLeftTopXY.y() - halfLength);
			break;
		case 2:	// 设置右上角的控制点的左上角坐标
			m_controlRect[i].setX(shapeLeftTopXY.x() + shapeWidth - halfLength);
			m_controlRect[i].setY(shapeLeftTopXY.y() - halfLength);
			break;
		case 3:	// 设置右边中点的控制点的左上角坐标
			m_controlRect[i].setX(shapeLeftTopXY.x() + shapeWidth - halfLength);
			m_controlRect[i].setY(shapeLeftTopXY.y() + shapeHeight / 2.0 - halfLength);
			break;
		case 4:	// 设置右下角的控制点的左上角坐标
			m_controlRect[i].setX(shapeLeftTopXY.x() + shapeWidth - halfLength);
			m_controlRect[i].setY(shapeLeftTopXY.y() + shapeHeight - halfLength);
			break;
		case 5:	// 设置下边中点的控制点的左上角坐标
			m_controlRect[i].setX(shapeLeftTopXY.x() + shapeWidth / 2.0 - halfLength);
			m_controlRect[i].setY(shapeLeftTopXY.y() + shapeHeight - halfLength);
			break;
		case 6:	// 设置左下角的控制点的左上角坐标
			m_controlRect[i].setX(shapeLeftTopXY.x() - halfLength);
			m_controlRect[i].setY(shapeLeftTopXY.y() + shapeHeight - halfLength);
			break;
		case 7:	// 设置左边中点的控制点的左上角坐标
			m_controlRect[i].setX(shapeLeftTopXY.x() - halfLength);
			m_controlRect[i].setY(shapeLeftTopXY.y() + shapeHeight / 2.0 - halfLength);
			break;
		default:
			break;
		}

		// 设置控制点的大小
		m_controlRect[i].setWidth(2.0 * halfLength);
		m_controlRect[i].setHeight(2.0 * halfLength);

		// 绘制控制点矩形
		painter.drawRect(m_controlRect[i]);
		// 填充控制点矩形为蓝色
		painter.fillRect(m_controlRect[i], QColor(128, 0, 128));
	}
}

void KShape::move(const QPointF &offset)
{
	// 平移矩形边界（需要再绘制图形才能将图形平移）
	m_startPoint += offset;
	m_endPoint += offset;
}

void KShape::moveTop(QPointF pos)
{
	if (pos.y() - m_endPoint.y() <= -25)
		m_startPoint.setY(pos.y());
}

void KShape::moveBottom(QPointF pos)
{
	if (pos.y() - m_startPoint.y() >= 25)
		m_endPoint.setY(pos.y());
}

void KShape::moveLeft(QPointF pos)
{
	if (pos.x() - m_endPoint.x() <= -25)
		m_startPoint.setX(pos.x());
}

void KShape::moveRight(QPointF pos)
{
	if (pos.x() - m_startPoint.x() >= 25)
		m_endPoint.setX(pos.x());
}

void KShape::moveTopLeft(QPointF pos)
{
	if (pos.y() - m_endPoint.y() <= -25 && pos.x() - m_endPoint.x() <= -25)
		m_startPoint = pos;
	else if (pos.y() - m_endPoint.y() > -25 && pos.x() - m_endPoint.x() <= -25)
		m_startPoint.setX(pos.x());
	else if (pos.y() - m_endPoint.y() <= -25 && pos.x() - m_endPoint.x() > -25)
		m_startPoint.setY(pos.y());
}

void KShape::moveTopRight(QPointF pos)
{
	if (pos.y() - m_endPoint.y() <= -25 && pos.x() - m_startPoint.x() >= 25)
	{
		m_startPoint.setY(pos.y());
		m_endPoint.setX(pos.x());
	}
	else if (pos.y() - m_endPoint.y() > -25 && pos.x() - m_startPoint.x() >= 25)
	{
		m_endPoint.setX(pos.x());
	}
	else if (pos.y() - m_endPoint.y() <= -25 && pos.x() - m_startPoint.x() < 25)
	{
		m_startPoint.setY(pos.y());
	}
}

void KShape::moveBottomLeft(QPointF pos)
{
	if (pos.y() - m_startPoint.y() >= 25 && pos.x() - m_endPoint.x() <= -25)
	{
		m_startPoint.setX(pos.x());
		m_endPoint.setY(pos.y());
	}
	else if (pos.x() - m_endPoint.x() > -25 && pos.y() - m_startPoint.y() >= 25)
	{
		m_endPoint.setY(pos.y());
	}
	else if (pos.x() - m_endPoint.x() <= -25 && pos.y() - m_startPoint.y() < 25)
	{
		m_startPoint.setX(pos.x());
	}
}

void KShape::moveBottomRight(QPointF pos)
{
	if (pos.y() - m_startPoint.y() >= 25 && pos.x() - m_startPoint.x() >= 25)
		m_endPoint = pos;
	else if (pos.y() - m_startPoint.y() < 25 && pos.x() - m_startPoint.x() >= 25)
		m_endPoint.setX(pos.x());
	else if (pos.y() - m_startPoint.y() >= 25 && pos.x() - m_startPoint.x() < 25)
		m_endPoint.setY(pos.y());
}

void KShape::setShapeScale(qreal scale)
{
	m_scaleFactor = scale;
}

qreal KShape::getShapeScale()
{
	return m_scaleFactor;
}

void KShape::setBorderWidth(int width)
{
	m_borderWidth = width;
}

void KShape::setBorderStyle(Qt::PenStyle style)
{
	m_borderStyle = style;
}

void KShape::setBorderColor(QRgb color)
{
	m_borderColor = color;
}

void KShape::setShapeColor(QRgb color)
{
	m_shapeColor = color;
}

QRgb KShape::getBorderColor()
{
	return m_borderColor;
}

Qt::PenStyle KShape::getBorderStyle()
{
	return m_borderStyle;
}

QRgb KShape::getShapeColor()
{
	return m_shapeColor;
}

int KShape::getBorderWidth()
{
	return m_borderWidth;
}

const int KShape::getControlRectIndex(QPoint pos)
{
	for (int i = 0; i < 8; i++)
	{
		if (m_controlRect[i].contains(pos))
			return i;
	}
	return -1;
}
