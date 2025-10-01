#include "RootOverlayWindow.h"
#include "ui_RootOverlayWindow.h"
#include <QKeyEvent>

RootOverlayWindow::RootOverlayWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RootOverlayWindow)
{
    ui->setupUi(this);

    connect(ui->closeButton, &QPushButton::clicked, this, &RootOverlayWindow::disappear);
}

RootOverlayWindow::~RootOverlayWindow()
{
    delete ui;
}

void RootOverlayWindow::disappear()
{
    close();
}

void RootOverlayWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        disappear();
        event->accept();
        return;
    }

    QMainWindow::keyPressEvent(event);
}
