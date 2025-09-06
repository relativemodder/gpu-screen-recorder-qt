#include "overlaywindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OverlayWindow w;
    w.show();
    return a.exec();
}
