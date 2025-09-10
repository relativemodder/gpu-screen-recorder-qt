#include <QMessageBox>
#include "overlaywindow.h"
#include "ui_overlaywindow.h"
#include <utils.h>

#include <LayerShellQt/window.h>

OverlayWindow::OverlayWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OverlayWindow)
{
    ui->setupUi(this);

    connect(ui->artButton, &QPushButton::clicked, this, &OverlayWindow::showAbout);
}

void OverlayWindow::showAbout()
{
    Utils::createMessageBox(
        this,
        "Oh, so you discovered... this.\n\n"
        "Haha, well done!"
    )->show();
}

OverlayWindow::~OverlayWindow()
{
    delete ui;
}
