#include "kborderstylebutton.h"

KBorderStyleButton::KBorderStyleButton(QWidget *parent)
	: QComboBox(parent)
{
	QStringList borderStyleItems;
	QTextCodec *codec = QTextCodec::codecForName("GBK");
	// 设置下拉选择样式
	borderStyleItems
		<< codec->toUnicode("——")
		<< "--------"
		<< "............."
		<< codec->toUnicode("—·—·—·");

	QListWidget *listWidget = new QListWidget(this);
	for (int i = 0; i < borderStyleItems.count(); i++)
	{
		QListWidgetItem *item = new QListWidgetItem(borderStyleItems.at(i));
		item->setTextAlignment(Qt::AlignCenter);
		listWidget->addItem(item);
	}
	QString qssStr = QString("color: #%1;").arg("FFFFFF");
	// 设置白色显示
	listWidget->setStyleSheet(qssStr);
	setModel(listWidget->model());
	setView(listWidget);
	// 设置画笔颜色
	m_pen.setColor(QColor(255, 255, 255));
	// 设置画笔宽度为2
	m_pen.setWidthF(2.0);
	connect(this, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &KBorderStyleButton::getPenStyle);
}

KBorderStyleButton::~KBorderStyleButton()
{
}

void KBorderStyleButton::paintEvent(QPaintEvent *event)
{
	// 绘制QCombox中选中的样式
	QPainter painter(this);
	painter.setPen(m_pen);
	painter.drawLine(QPoint(10, 20), QPoint(100, 20));
}

void KBorderStyleButton::getPenStyle(int index)
{
	switch (index)
	{
	case 0:
		// 实线
		emit setShapePen(Qt::SolidLine);
		setComBoxView(Qt::SolidLine);
		break;
	case 1:
		// 虚线
		emit setShapePen(Qt::DashLine);
		setComBoxView(Qt::DashLine);
		break;
	case 2:
		// 点线
		emit setShapePen(Qt::DotLine);
		setComBoxView(Qt::DotLine);
		break;
	case 3:
		// 点划线
		emit setShapePen(Qt::DashDotLine);
		setComBoxView(Qt::DashDotLine);
	default:
		break;
	}
}

void KBorderStyleButton::setComBoxView(Qt::PenStyle style)
{
	m_pen.setStyle(style);;
	update();
}
