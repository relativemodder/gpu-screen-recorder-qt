#include "RootOverlayWindow.h"
#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QTimer>
#include <QMessageBox>
#include "ui_RootOverlayWindow.h"

RootOverlayWindow* RootOverlayWindow::instance = nullptr;

RootOverlayWindow::RootOverlayWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RootOverlayWindow)
{
    ui->setupUi(this);
    RootOverlayWindow::instance = this;

    connect(ui->closeButton, &QPushButton::clicked, this, &RootOverlayWindow::disappear);
    connect(ui->settingsButton, &QPushButton::clicked, this, &RootOverlayWindow::settingsPressed);

    pageState = PageStateMain;

    ui->mainFrame->hide();

    mainPage = new MainPage(this);
    navigateTo(mainPage);
}

void RootOverlayWindow::settingsPressed()
{
    if (settingsPage == nullptr) {
        settingsPage = new SettingsPage();
    }

    if (pageState == PageStateMain) {
        navigateTo(settingsPage);
        pageState = PageStateSettings;
        ui->settingsButton->setText("  Go back");
        ui->settingsButton->setIcon(QIcon::fromTheme("edit-undo"));
    }
    else {
        navigateTo(mainPage);
        pageState = PageStateMain;
        ui->settingsButton->setText("  Settings");
        ui->settingsButton->setIcon(QIcon::fromTheme("preferences-other"));
    }
}

void RootOverlayWindow::navigateTo(QWidget *page)
{
    ui->stackedView->addWidget(page);
    ui->stackedView->setCurrentWidget(page);
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

    connect(timer, &QTimer::timeout, this, &RootOverlayWindow::playAppearAnimation);

    timer->start(100);
}

void RootOverlayWindow::playAppearAnimation() {

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
    connect(timer, &QTimer::timeout, ui->mainFrame, &QFrame::hide);
    timer->start(400);

    QTimer* timer1 = new QTimer(this);
    timer1->setSingleShot(true);
    connect(timer1, &QTimer::timeout, this, &RootOverlayWindow::hide);
    timer1->start(500);
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


void RootOverlayWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->x() > ui->mainFrame->width())
    {
        disappear();
    }

    QMainWindow::mousePressEvent(event);
}
