#include "RootOverlayWindow.h"
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QTimer>
#include "ui_RootOverlayWindow.h"

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
    animation->setDuration(400);
    animation->setEasingCurve(QEasingCurve::InOutCirc);
    animation->setStartValue(QPoint(-ui->mainFrame->width(), 0));
    animation->setEndValue(QPoint(0, 0));

    ui->mainFrame->show();

    animation->start();
}

void RootOverlayWindow::disappear()
{

    QPropertyAnimation *animation = new QPropertyAnimation(ui->mainFrame, "pos");
    animation->setDuration(400);
    animation->setStartValue(QPoint(0, 0));
    animation->setEasingCurve(QEasingCurve::InOutCirc);
    animation->setEndValue(QPoint(-ui->mainFrame->width(), 0));

    animation->start();

    QTimer* timer = new QTimer(this);
    timer->setSingleShot(true);

    connect(timer, &QTimer::timeout, this, &RootOverlayWindow::close);

    timer->start(400);
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
