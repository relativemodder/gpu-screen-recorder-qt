#ifndef ROOTOVERLAYWINDOW_H
#define ROOTOVERLAYWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

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
    ~RootOverlayWindow();

private:
    Ui::RootOverlayWindow *ui;

public slots:
    void disappear();
    void appear();
    void playAnimation();

protected:
    void keyPressEvent(QKeyEvent *event) override;
};
#endif // ROOTOVERLAYWINDOW_H
