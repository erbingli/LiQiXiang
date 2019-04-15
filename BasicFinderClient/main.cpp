#include "widget.h"
#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    QPixmap pixmap("F:/dahengtest/9.jpg");
    QSplashScreen splansh(pixmap);
    splansh.show();
    a.processEvents();
    Widget w;//正在创建主窗体，并初始化
    w.show();
    splansh.finish(&w);//在主窗体对象初始化完成后，结束启动画面，

    return a.exec();
}
