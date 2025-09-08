#include "overlaywindow.h"
#include "ui_overlaywindow.h"

OverlayWindow::OverlayWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OverlayWindow)
{
    ui->setupUi(this);
}

OverlayWindow::~OverlayWindow()
{
    delete ui;
}
