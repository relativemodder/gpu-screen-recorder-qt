#include "RootOverlayWindow.h"
#include <iostream>
#include <QApplication>
#include <LayerShellQt/shell.h>
#include <QDBusConnection>
#include <QDBusError>
#include <QDBusReply>
#include <QDBusInterface>
#include <QDBusConnectionInterface>
#include <QCommandLineParser>
#include <GsrDbus.h>


int main(int argc, char *argv[])
{
    setenv("USE_LSH", "0", 1);

    bool useLayerShell = qEnvironmentVariable("USE_LSH", "1") == "1";

    if (useLayerShell) {
        LayerShellQt::Shell::useLayerShell();
    }

    QApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription(
        QString("GPU Screen Recorder Qt Overlay.\n") +
        QString("A sidebar overlay UI for GPU Screen Recorder in the style of NVIDIA App.\n") +
        QString("The application is currently primarly designed for Wayland and can't be run on X11 (yet).\n\n") +
        QString("You can disable the use of `layer-shell` Wayland protocol by passing `USE_LSH=0` environment variable.")
    );
    auto helpOption = parser.addHelpOption();
    parser.process(a);

    if (parser.isSet(helpOption)) {
        return 0;
    }

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
    w.setWindowFlag(Qt::Tool);


    w.createWinId();

    if (useLayerShell) {
        LayerShellQt::Window *layerShell = LayerShellQt::Window::get(w.windowHandle());
        layerShell->setLayer(LayerShellQt::Window::LayerOverlay);
        layerShell->setKeyboardInteractivity(LayerShellQt::Window::KeyboardInteractivityNone);
        layerShell->setScope("gsr-ui");
    }

    gsrDbusObject.appear();

    return a.exec();
}
