#include <QtWidgets/QApplication>
#include <QDesktopwidget>

#include "ksvgeditor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDesktopWidget *desktop = QApplication::desktop();
    KSVGEditor w;
    // 将窗口移动至桌面中间
    w.move((desktop->width() - w.width()) / 2, (desktop->height() - w.height()) / 2);
    w.show();
    return a.exec();
}
