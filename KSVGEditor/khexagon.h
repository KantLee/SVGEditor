// -----------------------------------------------------------
// khexagon.h
// 创建者： 李康
// 创建时间： 2024/5/16
// 功能描述： 金山作业三：SVG编辑器——绘制六边形
// Copyright 2024 Kingsoft
// -----------------------------------------------------------

#ifndef _KSVGEDITOR_KHEXAGON_H_
#define _KSVGEDITOR_KHEXAGON_H_

#include <cmath>

#include "kshape.h"

class KHexagon : public KShape
{
	Q_OBJECT

public:
	explicit KHexagon(QObject *parent = Q_NULLPTR);
	~KHexagon();
	// 绘制六边形
	virtual void drawShape(QPaintDevice *parent = Q_NULLPTR) override;
	virtual KShapeType getShapeType() override;
};

#endif	// _KSVGEDITOR_KHEXAGON_H_
