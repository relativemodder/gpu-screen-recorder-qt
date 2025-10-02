#ifndef ROOTOVERLAYWINDOW_H
#define ROOTOVERLAYWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include "MainPage.h"
#include "SettingsPage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class RootOverlayWindow;
}
QT_END_NAMESPACE

enum PageState { PageStateMain, PageStateSettings };

class RootOverlayWindow : public QMainWindow
{
    Q_OBJECT

public:
    RootOverlayWindow(QWidget *parent = nullptr);
    static RootOverlayWindow* instance;
    void navigateTo(QWidget* page);
    ~RootOverlayWindow();

private:
    Ui::RootOverlayWindow *ui;
    MainPage *mainPage = nullptr;
    SettingsPage *settingsPage = nullptr;
    PageState pageState;

public slots:
    void disappear();
    void appear();
    void playAppearAnimation();
    void settingsPressed();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};
#endif // ROOTOVERLAYWINDOW_H
