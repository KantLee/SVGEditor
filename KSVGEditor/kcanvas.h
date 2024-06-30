// -----------------------------------------------------------
// kcanvas.h
// 创建者： 李康
// 创建时间： 2024/5/16
// 功能描述： 金山作业三：SVG编辑器——创建画布，进行绘画操作
// Copyright 2024 Kingsoft
// -----------------------------------------------------------

#ifndef _KSVGEDITOR_KCANVAS_H_
#define _KSVGEDITOR_KCANVAS_H_

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>

#include "kshape.h"

// 移动类型
enum class KMoveType
{
	None = 0,
	Move,
	Top,
	Bottom,
	Left,
	Right,
	TopRight,
	TopLeft,
	BottomLeft,
	BottomRight,
};


class KCanvas : public QWidget
{
	Q_OBJECT

public:
	enum class KDrawFlag
	{
		NoneDrawFlag = 0,
		MouseDrawFlag,	// 鼠标工具（第一个选择工具）
		LineDrawFlag,	// 直线
		CircleDrawFlag,	// 圆形
		RectDrawFlag,	// 正方形
		PentagonDrawFlag,	// 五边形
		HexagonDrawFlag,	// 六边形
		PentagramDrawFlag,	// 五角星
	};

	explicit KCanvas(QWidget *parent = Q_NULLPTR);
	~KCanvas();

	virtual bool eventFilter(QObject *watched, QEvent *event) override;
	virtual void paintEvent(QPaintEvent *event) override;	// 重写绘画事件
	virtual void mousePressEvent(QMouseEvent *event) override;	// 重写鼠标按下事件
	virtual void mouseMoveEvent(QMouseEvent *event) override;	// 重写鼠标移动事件
	virtual void mouseReleaseEvent(QMouseEvent *event) override;	// 重写鼠标释放事件
	KShape *getCurrentShape(QPointF pos); // 获取当前位置图形
	QList<KShape*> *getShapeList();

	void setCanvasWidth(int width);		// 设置画布宽度
	void setCanvasHeight(int height);	// 设置画布高度
	void zoomCanvas(qreal scale);	// 缩放画布上面的图形

	int getCanvasWidth();	// 获取画布宽度
	int getCanvasHeight();	// 获取画布高度

	void cleanCanvas();	// 清空画布

signals:
	void currentShapeBorderWidth(int width);
	void currentShapeBorderStyle(Qt::PenStyle style);
	void currntShapeBorderColor(QRgb color);
	void currntShapeColor(QRgb color);
	void shapeSelected(bool isSelected);

private:
	KShape *m_pCurrentShape = Q_NULLPTR;	// 当前绘画的图形
	QList<KShape*> *m_pShapeList = Q_NULLPTR;	// 保存已经绘画好的图形
	QPointF m_lastPos;	// 最后一个坐标点
	bool m_isLPress = false; // 标记鼠标左键
	bool m_isDrawing = false; // 是否为绘图
	bool m_isSelected = false; // 是否为选中
	KDrawFlag m_currentDrawFlag;
	KMoveType m_transType;	// 记录移动类型
	qreal m_scaleFactor;	// 缩放比例
	int m_canvasHeight, m_canvasWidth;	// 画布大小
	bool m_enableSelect;	// 是否可以拖拽移动、变换
	bool m_isCleanCanvas;	// 是否点击了清空画布按钮
};

#endif // _KSVGEDITOR_KCANVAS_H_
