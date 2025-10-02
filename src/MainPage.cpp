#include "MainPage.h"
#include <QPushButton>
#include "ui_MainPage.h"

MainPage::MainPage(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::MainPage)
{
    ui->setupUi(this);
    connect(ui->quitButton, &QPushButton::clicked, QApplication::instance(), &QApplication::quit);
}

MainPage::~MainPage()
{
    delete ui;
}

