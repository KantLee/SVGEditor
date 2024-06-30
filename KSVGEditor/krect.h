// -----------------------------------------------------------
// krect.h
// �����ߣ� �
// ����ʱ�䣺 2024/5/16
// ���������� ��ɽ��ҵ����SVG�༭����������������
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
	// ����������
	virtual void drawShape(QPaintDevice *parent = Q_NULLPTR) override;
	virtual KShapeType getShapeType() override;
};

#endif // _KSVGEDITOR_KRECT_H_