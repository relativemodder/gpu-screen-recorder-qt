#include <iostream>
#include <utils.h>

#include <cstdlib>
#include <LayerShellQt/window.h>
#include <iostream>

void Utils::executeIfKDE(std::function<void()> onKDEFunc, std::function<void()> elsewhereFunc) {
    const char* env = std::getenv("XDG_CURRENT_DESKTOP");
    if (!env) {
        elsewhereFunc();
        return;
    }

    if (std::string_view(env) == std::string_view("KDE")) {
        onKDEFunc();
    } else {
        elsewhereFunc();
    }
}

QMessageBox* Utils::createMessageBox(QWidget* parent, const QString text, QMessageBox::Icon icon) {
    auto ret = new QMessageBox(parent);

    ret->setIcon(icon);
    ret->setText(text);
    ret->createWinId();

    executeIfKDE([ret] {
        auto retSurface = LayerShellQt::Window::get(ret->windowHandle());
        if (!retSurface) {
            std::cerr << "surface == nullptr";
        }

        retSurface->setExclusiveZone(-1);
        retSurface->setLayer(LayerShellQt::Window::LayerOverlay);
        retSurface->setAnchors(LayerShellQt::Window::Anchor::AnchorNone);
    });

    return ret;
}
