#include <GsrDbus.h>
#include <RootOverlayWindow.h>

GsrDbus::GsrDbus(QObject *parent)
    : QObject{parent}
{}

void GsrDbus::appear()
{
    if (RootOverlayWindow::instance != nullptr) {
        if (qEnvironmentVariable("USE_LSH", "1") == "1") {
            RootOverlayWindow::instance->show();
        }
        else {
            RootOverlayWindow::instance->showFullScreen();
        }
        RootOverlayWindow::instance->appear();
    }
}

void GsrDbus::disappear()
{
    if (RootOverlayWindow::instance != nullptr) {
        RootOverlayWindow::instance->disappear();
    }
}

void GsrDbus::toggleShow()
{
    if (RootOverlayWindow::instance != nullptr) {
        if (RootOverlayWindow::instance->isHidden()) {
            appear();
        }
        else {
            disappear();
        }
    }
}
