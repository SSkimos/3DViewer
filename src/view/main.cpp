#include "mainwindow.h"
#include "myglwidget.h"

#include <QApplication>

//#include <QtOpenGL>
//#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showFullScreen();
    return a.exec();
}
