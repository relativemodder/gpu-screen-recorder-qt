#include <QMessageBox>
#include "overlaywindow.h"
#include "ui_overlaywindow.h"

OverlayWindow::OverlayWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OverlayWindow)
{
    ui->setupUi(this);

    connect(ui->artButton, &QPushButton::clicked, this, &OverlayWindow::showAbout);
}

void OverlayWindow::showAbout()
{
    QMessageBox::information(
        this, "GPU Screen Recorder Qt Overlay",
        "Oh, so you discovered... this.\n\n"
        "Haha, well done!");
}

OverlayWindow::~OverlayWindow()
{
    delete ui;
}
