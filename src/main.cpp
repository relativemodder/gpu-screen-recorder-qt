#include "overlaywindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OverlayWindow w;

    w.setAttribute(Qt::WA_TranslucentBackground, true);
    w.setAttribute(Qt::WA_ShowModal, true);

    w.setWindowFlags(
        Qt::FramelessWindowHint |
        Qt::WindowStaysOnTopHint
    );

    w.setWindowModality(Qt::WindowModal);

    w.showFullScreen();
    return a.exec();
}
