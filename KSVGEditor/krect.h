// -----------------------------------------------------------
// krect.h
// 创建者： 李康
// 创建时间： 2024/5/16
// 功能描述： 金山作业三：SVG编辑器——绘制正方形
// Copyright 2024 Kingsoft
// -----------------------------------------------------------

#ifndef _KSVGEDITOR_KRECT_H_
#define _KSVGEDITOR_KRECT_H_

#include "kshape.h"

class KRect : public KShape
{
	Q_OBJECT

public:
	explicit KRect(QObject *parent = Q_NULLPTR);
	~KRect();
	// 绘制正方形
	virtual void drawShape(QPaintDevice *parent = Q_NULLPTR) override;
	virtual KShapeType getShapeType() override;
};

#endif // _KSVGEDITOR_KRECT_H_
