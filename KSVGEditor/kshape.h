// -----------------------------------------------------------
// kshape.h
// 创建者： 李康
// 创建时间： 2024/5/16
// 功能描述： 金山作业三：SVG编辑器——图形的基类
// Copyright 2024 Kingsoft
// -----------------------------------------------------------

#ifndef _KSVGEDITOR_KSHAPE_H_
#define _KSVGEDITOR_KSHAPE_H_

#include <QObject>
#include <QPoint>
#include <QPainter>
#include <QPaintDevice>

enum class KShapeType
{
	None = 0,
	LineShapeType,	// 直线
	CircleShapeType,	// 圆形
	RectShapeType,	// 正方形
	PentagonShapeType,	// 五边形
	HexagonShapeType,	// 六边形
	PentagramShapeType,	// 五角星
};

class KShape : public QObject
{
	Q_OBJECT

public:
	explicit KShape(QObject *parent = Q_NULLPTR);
	virtual ~KShape();

	virtual void drawShape(QPaintDevice *parent = Q_NULLPTR) = 0;
	QPointF getStartPoint() const;	// 获取绘画起始坐标点
	QPointF getEndPoint() const;	// 获取绘画结束坐标点
	void setStartPoint(const QPointF &point);	// 设置绘画起始坐标点
	void setEndPoint(const QPointF &point);	// 设置绘画结束坐标点
	bool isShapeVaild() const;	// 判断绘画是否合法
	virtual KShapeType getShapeType();	// 获取绘图的类型
	QRectF getShapeRect();	// 获取图形的边界矩形
	void drawOutline(QPaintDevice *parent = Q_NULLPTR);	// 绘制外部轮毂
	void drawSelectedHighlight(QPaintDevice* parent = Q_NULLPTR, bool drawControl = true);	// 选中图形的高亮部分
	void move(const QPointF &offset);	// 移动图形
	void moveTop(QPointF pos);	// 移动上边界
	void moveBottom(QPointF pos);	// 移动下边界
	void moveLeft(QPointF pos);	// 移动左边界
	void moveRight(QPointF pos);	// 移动右边界
	void moveTopLeft(QPointF pos);	// 移动左上角
	void moveTopRight(QPointF pos);	// 移动右上角
	void moveBottomLeft(QPointF pos);	// 移动左下角
	void moveBottomRight(QPointF pos);	// 移动右下角
	void setShapeScale(qreal scale);	// 设置图形的缩放比例
	qreal getShapeScale();	// 获取图形的缩放比例
	void setBorderWidth(int width);	// 设置图形的边框宽度
	void setBorderStyle(Qt::PenStyle style);	// 设置图形的边框样式
	void setBorderColor(QRgb color);	// 设置图形的边框颜色
	void setShapeColor(QRgb color);	// 设置图形的填充颜色
	QRgb getBorderColor();	// 获取图形的边框颜色
	Qt::PenStyle getBorderStyle();	// 获取图形的边框样式
	QRgb getShapeColor();	// 获取图形的填充颜色
	int getBorderWidth();	// 获取图形的边框宽度
	const int getControlRectIndex(QPoint pos);	// 根据点击的位置返回控制点的下标

private:
	qreal m_scaleFactor;	// 缩放比例
	QPointF m_startPoint; // 起始坐标
	QPointF m_endPoint; // 结束坐标
	int m_borderWidth;	// 边框宽度
	Qt::PenStyle m_borderStyle;	// 边框样式
	QRgb m_borderColor;// 边框颜色
	QRgb m_shapeColor;	// 填充颜色
	QRectF m_controlRect[8];	// 矩形的八个控制点，从左上角开始顺时针排序
};

#endif	// _KSVGEDITOR_KSHAPE_H_
