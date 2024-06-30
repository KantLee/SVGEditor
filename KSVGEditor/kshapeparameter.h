// -----------------------------------------------------------
// kshapeparameter.h
// 创建者： 李康
// 创建时间： 2024/5/16
// 功能描述： 金山作业三：SVG编辑器——用来设置保存绘制图形参数的类，单例模式
// Copyright 2024 Kingsoft
// -----------------------------------------------------------

#ifndef _KSVGEDITOR_KSHAPEPARAMETER_H
#define _KSVGEDITOR_KSHAPEPARAMETER_H

#include "kcanvas.h"

class KShapeParameter
{
public:
	static KShapeParameter *getInstance();
	static void deleteGlobalData();
	void setDrawFlag(KCanvas::KDrawFlag flag);	// 设置绘画标志
	KCanvas::KDrawFlag getDrawFlag() const;	// 获取当前的绘图标志
	qreal getShapeScale();	// 获取图形缩放比例
	qreal getCanvasScale();	// 获取画布缩放比例
	void setShapeScale(qreal scale);	// 设置图形缩放比例
	void setCanvasScale(qreal scale);	// 设置画布缩放比例
	void setCurrentShape(KShape *shape); //设置当前图形对象
	KShape *getCurrentShape(); //获取当前图形对象
	void setBorderWidth(int width);	// 设置图形边框宽度
	int getBorderWidth();	// 获取图形边框宽度
	void setBorderStyle(Qt::PenStyle style);	// 设置图形边框样式
	Qt::PenStyle getBorderStyle();	// 获取图形边框样式
	void setBorderColor(QRgb color);	// 设置图形边框颜色
	QRgb getBorderColor();	// 获取边框颜色
	void setShapeColor(QRgb color);	// 设置图形填充颜色
	QRgb getShapeColor();	// 获取图形颜色

private:
	KShapeParameter() = default;
	KShapeParameter(const KShapeParameter &other) = delete;
	KShapeParameter &operator=(const KShapeParameter &other) = delete;
	static KShapeParameter *s_shapeParameterObj;
	KCanvas::KDrawFlag m_drawFlag = KCanvas::KDrawFlag::NoneDrawFlag;
	qreal m_shapeScale = 1.0;	// 图形缩放比例，默认1.0
	qreal m_canvasScale = 1.0;	// 画布缩放比例，默认1.0
	int m_borderWidth = 2.0;	// 边框宽度，默认为2.0
	Qt::PenStyle m_borderStyle = Qt::SolidLine;	// 图形边框样式，默认为直线
	QRgb m_borderColor = qRgb(0, 0, 0);	// 图形边框颜色，默认为黑色
	QRgb m_shapeColor = qRgb(255, 255, 255);	// 图形填充颜色，默认为白色
	KShape *m_currentShape = Q_NULLPTR;	// 当前图形对象
};

#endif // _KSVGEDITOR_KSHAPEPARAMETER_H
