// -----------------------------------------------------------
// kshapefactory.h
// 创建者： 李康
// 创建时间： 2024/5/16
// 功能描述： 金山作业三：SVG编辑器——图形工厂
// Copyright 2024 Kingsoft
// -----------------------------------------------------------

#ifndef _K_KSHAPEFACTORY_H_
#define _K_KSHAPEFACTORY_H_

#include <QObject>

#include "kcanvas.h"
#include "kline.h"
#include "kcircle.h"
#include "krect.h"
#include "kpentagon.h"
#include "khexagon.h"
#include "kpentagram.h"

class KShapeFactory : public QObject
{
	Q_OBJECT

public:
	explicit KShapeFactory(QObject *parent = Q_NULLPTR);
	~KShapeFactory();

	static KShape *createShape(KCanvas::KDrawFlag drawFlag);
};

#endif // _K_KSHAPEFACTORY_H_
