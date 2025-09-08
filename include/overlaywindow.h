#ifndef OVERLAYWINDOW_H
#define OVERLAYWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class OverlayWindow;
}
QT_END_NAMESPACE

class OverlayWindow : public QMainWindow
{
    Q_OBJECT

public:
    OverlayWindow(QWidget *parent = nullptr);
    ~OverlayWindow();

private:
    Ui::OverlayWindow *ui;

public slots:
    void showAbout();
};
#endif // OVERLAYWINDOW_H
