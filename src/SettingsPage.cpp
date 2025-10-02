#include "SettingsPage.h"
#include "ui_SettingsPage.h"
#include <QVariant>

SettingsPage::SettingsPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SettingsPage)
{
    ui->setupUi(this);

    setupCodecs();
}

void SettingsPage::setupCodecs()
{
    ui->codecComboBox->insertItem(0, "Auto", QVariant("auto"));
    ui->codecComboBox->insertItem(1, "H264", QVariant("h264"));
    ui->codecComboBox->insertItem(2, "HEVC", QVariant("hevc"));
    ui->codecComboBox->insertItem(3, "AV1", QVariant("av1"));
    ui->codecComboBox->insertItem(4, "VP8", QVariant("vp8"));
    ui->codecComboBox->insertItem(5, "VP9", QVariant("vp9"));
}

SettingsPage::~SettingsPage()
{
    delete ui;
}
