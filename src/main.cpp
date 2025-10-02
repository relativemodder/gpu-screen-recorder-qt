#include "RootOverlayWindow.h"
#include <iostream>
#include <QApplication>
#include <LayerShellQt/shell.h>
#include <QDBusConnection>
#include <QDBusError>
#include <QDBusReply>
#include <QDBusInterface>
#include <QDBusConnectionInterface>
#include <GsrDbus.h>


int main(int argc, char *argv[])
{
    bool useLayerShell = qEnvironmentVariable("USE_LSH", "1") == "1";

    if (useLayerShell) {
        LayerShellQt::Shell::useLayerShell();
    }

    QApplication a(argc, argv);
    QDBusConnection connection = QDBusConnection::sessionBus();

    if (!connection.isConnected()) {
        qWarning("Cannot connect to the D-Bus session bus.\n"
                 "To start it, run:\n"
                 "\teval `dbus-launch --auto-syntax`\n");
        return 1;
    }

    QDBusInterface iface(SERVICE_NAME, "/");

    if (iface.isValid()) {
        iface.call("toggleShow");
        return 0;
    }

    qWarning("No valid instances of GSR Qt Overlay found. Creating a new one.\n");

    if (!connection.registerService(SERVICE_NAME)) {
        qWarning("%s\n", qPrintable(connection.lastError().message()));
        return 1;
    }

    GsrDbus gsrDbusObject;
    connection.registerObject("/", &gsrDbusObject, QDBusConnection::ExportAllSlots);

    RootOverlayWindow w;
    w.setAttribute(Qt::WA_TranslucentBackground);
    w.setWindowFlag(Qt::NoTitleBarBackgroundHint);

    if (useLayerShell) {
        LayerShellQt::Window *layerShell = LayerShellQt::Window::get((QWindow*)w.window());
        layerShell->setLayer(LayerShellQt::Window::LayerOverlay);
        layerShell->setScope("gsr-ui");
    }

    gsrDbusObject.appear();

    return a.exec();
}
