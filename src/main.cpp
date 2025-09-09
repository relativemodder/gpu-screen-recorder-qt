#include "overlaywindow.h"

#include <QApplication>
#include <LayerShellQt/shell.h>
#include <iostream>
#include <utils.h>

int main(int argc, char *argv[])
{
    Utils::executeIfKDE([] {
        LayerShellQt::Shell::useLayerShell();
    });

    QApplication a(argc, argv);
    OverlayWindow w;

    w.setAttribute(Qt::WA_TranslucentBackground, true);
    w.setAttribute(Qt::WA_ShowModal, true);

    w.setWindowFlags(
        Qt::FramelessWindowHint |
        Qt::WindowStaysOnTopHint
    );

    w.setWindowModality(Qt::WindowModal);
    w.createWinId();

    Utils::executeIfKDE([&w] {
        auto surface = LayerShellQt::Window::get(w.windowHandle());

        if (!surface) {
            std::cerr << "surface == nullptr";
        }

        surface->setExclusiveZone(-1);
        surface->setLayer(LayerShellQt::Window::LayerOverlay);

        w.show();
    }, [&w] {
        w.showFullScreen();
    });

    return a.exec();
}
