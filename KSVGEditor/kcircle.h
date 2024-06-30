// -----------------------------------------------------------
// kcircle.h
// 创建者： 李康
// 创建时间： 2024/5/16
// 功能描述： 金山作业三：SVG编辑器——绘制圆形
// Copyright 2024 Kingsoft
// -----------------------------------------------------------

#ifndef _KSVGEDITOR_KCIRCLE_H_
#define _KSVGEDITOR_KCIRCLE_H_

#include "kshape.h"

class KCircle : public KShape
{
	Q_OBJECT

public:
	explicit KCircle(QObject *parent = Q_NULLPTR);
	~KCircle();
	// 绘制圆形
	virtual void drawShape(QPaintDevice *parent = Q_NULLPTR) override;
	virtual KShapeType getShapeType() override;
};

#endif // _KSVGEDITOR_KCIRCLE_H_
