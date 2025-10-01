#include "RootOverlayWindow.h"
#include "ui_RootOverlayWindow.h"
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QTimer>

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

void RootOverlayWindow::appear() {
    ui->mainFrame->move(-ui->mainFrame->width(), 0);
    ui->mainFrame->hide();

    QTimer* timer = new QTimer(this);
    timer->setSingleShot(true);

    connect(timer, &QTimer::timeout, this, &RootOverlayWindow::playAnimation);

    timer->start(100);
}

void RootOverlayWindow::playAnimation() {
    QPropertyAnimation *animation = new QPropertyAnimation(ui->mainFrame, "pos");
    animation->setDuration(300);
    animation->setStartValue(QPoint(-ui->mainFrame->width(), 0));
    animation->setEndValue(QPoint(0, 0));

    ui->mainFrame->show();

    animation->start();
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
