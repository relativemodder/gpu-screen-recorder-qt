#include "overlaywindow.h"
#include "ui_overlaywindow.h"

OverlayWindow::OverlayWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OverlayWindow)
{
    ui->setupUi(this);
}

OverlayWindow::~OverlayWindow()
{
    delete ui;
}
