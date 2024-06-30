#include "kshapeparameter.h"

KShapeParameter *KShapeParameter::s_shapeParameterObj = nullptr;

KShapeParameter *KShapeParameter::getInstance()
{
    if (s_shapeParameterObj == nullptr)
        s_shapeParameterObj = new KShapeParameter();
    return s_shapeParameterObj;
}

void KShapeParameter::deleteGlobalData()
{
    delete s_shapeParameterObj;
    s_shapeParameterObj = nullptr;
}

void KShapeParameter::setDrawFlag(KCanvas::KDrawFlag flag)
{
    m_drawFlag = flag;
}

KCanvas::KDrawFlag KShapeParameter::getDrawFlag() const
{
    return m_drawFlag;
}

qreal KShapeParameter::getShapeScale()
{
    return m_shapeScale;
}

qreal KShapeParameter::getCanvasScale()
{
    return m_canvasScale;
}

void KShapeParameter::setShapeScale(qreal scale)
{
    m_shapeScale = scale;
}

void KShapeParameter::setCanvasScale(qreal scale)
{
    m_canvasScale = scale;
}

void KShapeParameter::setCurrentShape(KShape *shape)
{
    m_currentShape = shape;
}

KShape *KShapeParameter::getCurrentShape()
{
    return m_currentShape;
}

void KShapeParameter::setBorderWidth(int width)
{
    m_borderWidth = width;
    m_currentShape->setBorderWidth(width);
}

int KShapeParameter::getBorderWidth()
{
    return m_borderWidth;
}

void KShapeParameter::setBorderStyle(Qt::PenStyle style)
{
    m_borderStyle = style;
    m_currentShape->setBorderStyle(style);
}

Qt::PenStyle KShapeParameter::getBorderStyle()
{
    return m_borderStyle;
}

void KShapeParameter::setBorderColor(QRgb color)
{
    m_borderColor = color;
    m_currentShape->setBorderColor(color);
}

QRgb KShapeParameter::getBorderColor()
{
    return m_borderColor;
}

void KShapeParameter::setShapeColor(QRgb color)
{
    m_shapeColor = color;
    m_currentShape->setShapeColor(color);
}

QRgb KShapeParameter::getShapeColor()
{
    return m_shapeColor;
}
