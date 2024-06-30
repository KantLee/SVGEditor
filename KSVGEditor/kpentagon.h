// -----------------------------------------------------------
// kpentagon.h
// �����ߣ� �
// ����ʱ�䣺 2024/5/16
// ���������� ��ɽ��ҵ����SVG�༭���������������
// Copyright 2024 Kingsoft
// -----------------------------------------------------------

#ifndef _KSVGEDITOR_KPENTAGON_H_
#define _KSVGEDITOR_KPENTAGON_H_

#include "kshape.h"

class KPentagon : public KShape
{
	Q_OBJECT

public:
	explicit KPentagon(QObject *parent = Q_NULLPTR);
	~KPentagon();
	// ���������
	virtual void drawShape(QPaintDevice *parent = Q_NULLPTR) override;
	virtual KShapeType getShapeType() override;
};

#endif	// _KSVGEDITOR_KPENTAGON_H_