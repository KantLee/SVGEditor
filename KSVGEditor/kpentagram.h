// -----------------------------------------------------------
// kpentagram.h
// 创建者： 李康
// 创建时间： 2024/5/16
// 功能描述： 金山作业三：SVG编辑器——绘制五角星
// Copyright 2024 Kingsoft
// -----------------------------------------------------------

#ifndef _KSVGEDITOR_KPENTAGRAM_H_
#define _KSVGEDITOR_KPENTAGRAM_H_

#include <cmath>

#include "kshape.h"

class KPentagram : public KShape
{
	Q_OBJECT

public:
	explicit KPentagram(QObject *parent = Q_NULLPTR);
	~KPentagram();
	// 绘制五角星
	virtual void drawShape(QPaintDevice *parent = Q_NULLPTR) override;
	virtual KShapeType getShapeType() override;
};

#endif	// _KSVGEDITOR_KPENTAGRAM_H_
