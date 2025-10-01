#include "RootOverlayWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RootOverlayWindow w;
    w.setAttribute(Qt::WA_TranslucentBackground);
    w.setWindowFlag(Qt::NoTitleBarBackgroundHint);
    w.showFullScreen();

    return a.exec();
}
