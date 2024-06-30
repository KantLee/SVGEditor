// -----------------------------------------------------------
// ksvgeditor.h
// 创建者： 李康
// 创建时间： 2024/5/16
// 功能描述： 金山作业三：SVG编辑器——主界面
// Copyright 2024 Kingsoft
// -----------------------------------------------------------

#ifndef _K_KSVGEDITOR_H_
#define _K_KSVGEDITOR_H_

#include <QtWidgets/QMainWindow>
#include <QColorDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QImage>
#include <QPixmap>

#include "ui_ksvgeditor.h"
#include "kshapeparameter.h"

class KSVGEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit KSVGEditor(QWidget *parent = Q_NULLPTR);
    void moveCanvasToCenter();  // 将画布移动到QScrollArea中间
    // 顶部工具栏相关操作
    void onCleanCanvasClicked();
    void onExportPNGBtnClicked();
    // 左侧工具栏相关操作
    void onSelectButtonClicked();
    void onLineButtonClicked();
    void onCircleButtonClicked();
    void onRectButtonClicked();
    void onPentagonButtonClicked();
    void onHexagonButtonClicked();
    void onPentagramButtonClicked();
    // 右侧画布参数相关操作
    void onSetCanvasWidth(int width);   // 设置画布宽度
    void onSetCanvasHeight(int height);   // 设置画布高度
    void onZoomCanvas(qreal scale);   // 缩放画布
    void setCanvasColor();  // 设置画布颜色
    // 右侧图形参数相关操作
    void onSetShapeBorderWidth(int width);  // 设置图形边框宽度
    void onSetBorderWidthSpinBoxValue(int width);   // 设置调整图形边框宽度的SpinBox的值
    void onSetShapeBorderStyle(Qt::PenStyle style); // 设置图形边框样式
    void onSetShapeBorderColor();   // 设置图形边框颜色
    void onSetShapeBorderColorButtonColor(QRgb color);  // 设置调整图形边框颜色的按钮颜色
    void onSetShapeColor();   // 设置图形填充颜色
    void onSetShapeColorButtonColor(QRgb color);  // 设置调整图形填充颜色的按钮颜色
    void onIsSelectShape(bool isSelected);  // 是否选中图形的槽函数

protected:
    QRgb selectColor(); // 打开颜色选择对话框选择一个颜色
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

signals:
    void onDrawingFlagChanged(KCanvas::KDrawFlag drawFlag);

private:
    Ui::KSVGEditorClass ui;
    double m_currentCanvasScale; // 画布当前的缩放比例
    bool m_isSelectShape; // 是否选中了图形
    int m_preShapeBorderWidth;  // 上一个选择的图形边框宽度
    bool m_isRestoreWidth;  // 是否恢复图形边框的值
};

#endif // _K_KSVGEDITOR_H_
