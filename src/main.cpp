#include "view/window.h"

int main(int argc, char *argv[])
{
    setenv("LC_NUMERIC", "C", 1);
    QApplication a(argc, argv);
    Window w;
    w.showFullScreen();
    return a.exec();
}
