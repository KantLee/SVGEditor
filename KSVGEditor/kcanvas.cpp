#include "kcanvas.h"
#include "kshapefactory.h"
#include "kshapeparameter.h"

KCanvas::KCanvas(QWidget *parent)
	: QWidget(parent)
	, m_pShapeList(new QList<KShape*>)
	, m_isLPress(false)
	, m_isDrawing(false)
	, m_isSelected(false)
	, m_transType(KMoveType::None)
	, m_scaleFactor(1.0)
	, m_canvasWidth(600)
	, m_canvasHeight(600)
	, m_currentDrawFlag(KDrawFlag::NoneDrawFlag)
	, m_enableSelect(false)
	, m_isCleanCanvas(false)
{
	setAttribute(Qt::WA_StyledBackground, true);
	//设置鼠标追踪
	setMouseTracking(true);
	//单击获取焦点
	setFocusPolicy(Qt::ClickFocus);
	// 开启鼠标悬停
	this->setAttribute(Qt::WA_Hover, true);
	// 安装事件过滤器
	this->installEventFilter(this);
}

KCanvas::~KCanvas()
{
	qDeleteAll(*m_pShapeList);
	delete m_pShapeList;
}

bool KCanvas::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == this)
	{
		if (event->type() == QEvent::HoverMove)
		{
			if (!m_pCurrentShape)
				return QWidget::eventFilter(watched, event);
			// 排除当前图形为五角星的情况
			if (m_pCurrentShape->getShapeType() == KShapeType::PentagramShapeType)
				return QWidget::eventFilter(watched, event);
			if (m_currentDrawFlag == KDrawFlag::MouseDrawFlag)
			{
				QHoverEvent *e = static_cast<QHoverEvent*>(event);
				// 根据鼠标位置更改鼠标样式
				int controlPos = m_pCurrentShape->getControlRectIndex(e->pos());
				switch (controlPos)
				{
				case 0:	// 左上角
					setCursor(Qt::SizeFDiagCursor);
					break;
				case 1:	// 顶部中间
					setCursor(Qt::SizeVerCursor);
					break;
				case 2:	// 右上角
					setCursor(Qt::SizeBDiagCursor);
					break;
				case 3:	// 右边中间
					setCursor(Qt::SizeHorCursor);
					break;
				case 4:	// 右下角
					setCursor(Qt::SizeFDiagCursor);
					break;
				case 5:	// 底部中间
					setCursor(Qt::SizeVerCursor);
					break;
				case 6:	// 左下角
					setCursor(Qt::SizeBDiagCursor);
					break;
				case 7:	// 左边中间
					setCursor(Qt::SizeHorCursor);
					break;
				default:	// 其他位置
					setCursor(Qt::ArrowCursor);
					break;
				}
			}
		}
	}
	return QWidget::eventFilter(watched, event);
}

// 重写绘画事件
void KCanvas::paintEvent(QPaintEvent *event)
{
	// 绘图
	if (!m_pShapeList->isEmpty())
	{
		for (QList<KShape*>::iterator it = m_pShapeList->begin();
			it != m_pShapeList->end(); ++it)
			(*it)->drawShape(this);
	}
	else if(m_isCleanCanvas)	// 如果没有绘制的图形，并且点击了清空画布，则return
	{
		return;
	}
	// 如果当前在绘制图形或者选中了图形
	if (m_pCurrentShape)
	{
		// 如果是处于移动状态，只绘制高亮即可
		if (m_currentDrawFlag == KDrawFlag::MouseDrawFlag)
		{
			// 如果是五角星则不进行控制点的绘制
			if (m_pCurrentShape->getShapeType() == KShapeType::PentagramShapeType)
				m_pCurrentShape->drawSelectedHighlight(this, false);
			else
				m_pCurrentShape->drawSelectedHighlight(this, true);
		}
		else
		{
			// 如果是在绘制矩形以外的图形，则除了绘制矩形边界外还要绘制图形
			if (m_currentDrawFlag != KDrawFlag::RectDrawFlag)
				m_pCurrentShape->drawShape(this);
			m_pCurrentShape->drawOutline(this);
		}
	}
}

// 重写鼠标按下事件
void KCanvas::mousePressEvent(QMouseEvent *event)
{
	// 检查当前是缩放比例
	qreal scale = KShapeParameter::getInstance()->getShapeScale();
	if (scale != 1.0)
	{
		QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("请先恢复缩放比例为1.0再进行操作"));
		return;
	}
	// 获取当前的绘制标志（点击的是左侧哪个按钮）
	m_currentDrawFlag = KShapeParameter::getInstance()->getDrawFlag();
	// 如果没有点击左侧的按钮（即程序刚运行时），什么都不做
	if (m_currentDrawFlag == KDrawFlag::NoneDrawFlag)
		return;
	m_lastPos = event->pos();	// 获取按下的位置
	m_isCleanCanvas = false;	// 非清空画布状态
	// 如果是移动工具
	if (m_currentDrawFlag == KDrawFlag::MouseDrawFlag)
	{
		// 点击左键
		if (event->buttons() == Qt::LeftButton)
		{
			m_isLPress = true;	// 设置左键按下标志
			// 获取点击位置的图形
			KShape *shape = getCurrentShape(m_lastPos);
			if (shape)
			{
				m_pCurrentShape = shape;
				int controlPos = m_pCurrentShape->getControlRectIndex(event->pos());
				switch (controlPos)
				{
				case 0:	// 左上角
					m_transType = KMoveType::TopLeft;
					break;
				case 1:	// 顶部中间
					m_transType = KMoveType::Top;
					break;
				case 2:	// 右上角
					m_transType = KMoveType::TopRight;
					break;
				case 3:	// 右边中间
					m_transType = KMoveType::Right;
					break;
				case 4:	// 右下角
					m_transType = KMoveType::BottomRight;
					break;
				case 5:	// 底部中间
					m_transType = KMoveType::Bottom;
					break;
				case 6:	// 左下角
					m_transType = KMoveType::BottomLeft;
					break;
				case 7:	// 左边中间
					m_transType = KMoveType::Left;
					break;
				default:	// 其他位置
					m_transType = KMoveType::Move;
					break;
				}
				m_enableSelect = true;
				// 设置当前选择的图形
				KShapeParameter::getInstance()->setCurrentShape(m_pCurrentShape);
				// 已经选择了图形
				emit shapeSelected(true);
				// 获取边框宽度
				int width = m_pCurrentShape->getBorderWidth();
				emit currentShapeBorderWidth(width);
				// 获取边框样式
				Qt::PenStyle style = m_pCurrentShape->getBorderStyle();
				emit currentShapeBorderStyle(style);
				// 获取边框颜色
				QRgb rgb = m_pCurrentShape->getBorderColor();
				emit currntShapeBorderColor(rgb);
				// 获取图形填充颜色
				rgb = m_pCurrentShape->getShapeColor();
				emit currntShapeColor(rgb);
				update();
			}
		}
	}
	else
	{
		if (event->buttons() == Qt::LeftButton)
		{
			m_isLPress = true;	// 设置左键按下标志
			// 创建一个图形
			m_pCurrentShape = KShapeFactory::createShape(m_currentDrawFlag);
			// 设置起始的坐标点
			m_pCurrentShape->setStartPoint(m_lastPos);
			// 设置结束的坐标点
			m_pCurrentShape->setEndPoint(m_lastPos);
			m_isDrawing = true;	// 设置绘图标志
		}
	}
}

// 重写鼠标移动事件
void KCanvas::mouseMoveEvent(QMouseEvent *event)
{
	if (m_currentDrawFlag == KDrawFlag::NoneDrawFlag)
		return;
	// 获取鼠标位置
	QPoint nowPos = event->pos();
	if (m_currentDrawFlag == KDrawFlag::MouseDrawFlag)
	{
		if(m_enableSelect)
		{
			QPointF offset = nowPos - m_lastPos;
			switch (m_transType)
			{
			case KMoveType::Move:
				m_pCurrentShape->move(offset);
				break;
			case KMoveType::Top:
				m_pCurrentShape->moveTop(nowPos);
				break;
			case KMoveType::Bottom:
				m_pCurrentShape->moveBottom(nowPos);
				break;
			case KMoveType::Left:
				m_pCurrentShape->moveLeft(nowPos);
				break;
			case KMoveType::Right:
				m_pCurrentShape->moveRight(nowPos);
				break;
			case KMoveType::TopLeft:
				m_pCurrentShape->moveTopLeft(nowPos);
				break;
			case KMoveType::TopRight:
				m_pCurrentShape->moveTopRight(nowPos);
				break;
			case KMoveType::BottomRight:
				m_pCurrentShape->moveBottomRight(nowPos);
				break;
			case KMoveType::BottomLeft:
				m_pCurrentShape->moveBottomLeft(nowPos);
				break;
			default:
				break;
			}
			update();
			m_lastPos = nowPos;
		}
	}
	// 如果是绘图状态
	else
	{
		if (m_isLPress)
		{
			if (m_isDrawing && m_pCurrentShape)
			{
				m_pCurrentShape->setEndPoint(nowPos);
				update();
			}
		}
	}
}

// 重写鼠标释放事件
void KCanvas::mouseReleaseEvent(QMouseEvent *event)
{
	if (m_currentDrawFlag == KDrawFlag::NoneDrawFlag)
		return;
	if (m_currentDrawFlag == KDrawFlag::MouseDrawFlag)
	{
		if (event->button() == Qt::LeftButton)
		{
			m_isLPress = false;
			m_enableSelect = false;
		}
			
	}
	else
	{
		if (event->button() == Qt::LeftButton)
		{
			m_isLPress = false;
			if (m_isDrawing && m_pCurrentShape)
			{
				m_pCurrentShape->setEndPoint(event->pos());
				if (m_pCurrentShape->isShapeVaild())
					m_pShapeList->append(m_pCurrentShape);
				else
					delete m_pCurrentShape;
				m_pCurrentShape = nullptr;
				m_isDrawing = false;
				update();
			}
		}
	}
}

// 获取当前点击位置的图形
KShape *KCanvas::getCurrentShape(QPointF pos)
{
	for (KShape *shape : *m_pShapeList)
	{
		if (shape->getShapeRect().contains(pos))
		{
			return shape;
		}
	}
	// 没有图形返回空
	return Q_NULLPTR;
}

QList<KShape*> *KCanvas::getShapeList()
{
	return m_pShapeList;
}

// 设置画布宽度
void KCanvas::setCanvasWidth(int width)
{
	m_canvasWidth = width;
	resize(m_canvasWidth, m_canvasHeight);
}

// 设置画布高度
void KCanvas::setCanvasHeight(int height)
{
	m_canvasHeight = height;
	resize(m_canvasWidth, m_canvasHeight);
}

// 缩放画布
void KCanvas::zoomCanvas(qreal scale)
{
	// 缩放画布
	resize(m_canvasWidth * scale, m_canvasHeight * scale);
	qreal shapeScale = KShapeParameter::getInstance()->getShapeScale();
	// 缩放画布上面的图形
	for (auto shape : *m_pShapeList)
	{
		shape->setShapeScale(shapeScale);
	}
	update();
}

// 获取画布宽度
int KCanvas::getCanvasWidth()
{
	return m_canvasWidth;
}

// 获取画布高度
int KCanvas::getCanvasHeight()
{
	return m_canvasHeight;
}

// 清空画布
void KCanvas::cleanCanvas()
{
	m_pShapeList->clear();
	m_isCleanCanvas = true;
	update();
}
