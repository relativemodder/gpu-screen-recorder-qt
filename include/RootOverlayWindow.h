#ifndef ROOTOVERLAYWINDOW_H
#define ROOTOVERLAYWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include "MainPage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class RootOverlayWindow;
}
QT_END_NAMESPACE

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
    MainPage *mainPage;

public slots:
    void disappear();
    void appear();
    void playAppearAnimation();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};
#endif // ROOTOVERLAYWINDOW_H
