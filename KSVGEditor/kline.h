// -----------------------------------------------------------
// kline.h
// 创建者： 李康
// 创建时间： 2024/5/16
// 功能描述： 金山作业三：SVG编辑器——绘制直线
// Copyright 2024 Kingsoft
// -----------------------------------------------------------

#ifndef _KSVGEDITOR_KLINE_H_
#define _KSVGEDITOR_KLINE_H_

#include "kshape.h"

class KLine : public KShape
{
	Q_OBJECT

public:
	explicit KLine(QObject *parent = Q_NULLPTR);
	~KLine();
	// 绘制直线
	virtual void drawShape(QPaintDevice *parent = Q_NULLPTR) override;
	virtual KShapeType getShapeType() override;
};

#endif	// _KSVGEDITOR_KLINE_H_
