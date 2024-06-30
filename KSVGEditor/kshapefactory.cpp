#include "kshapefactory.h"

KShapeFactory::KShapeFactory(QObject *parent)
	: QObject(parent)
{
}

KShapeFactory::~KShapeFactory()
{
}

KShape *KShapeFactory::createShape(KCanvas::KDrawFlag drawFlag)
{
	switch (drawFlag)
	{
	case KCanvas::KDrawFlag::LineDrawFlag:
		return new KLine;
	case KCanvas::KDrawFlag::CircleDrawFlag:
		return new KCircle;
	case KCanvas::KDrawFlag::RectDrawFlag:
		return new KRect;
	case KCanvas::KDrawFlag::PentagonDrawFlag:
		return new KPentagon;
	case KCanvas::KDrawFlag::HexagonDrawFlag:
		return new KHexagon;
	case KCanvas::KDrawFlag::PentagramDrawFlag:
		return new KPentagram;
	default:
		break;
	}
	return Q_NULLPTR;
}
