#ifndef UTILS_H
#define UTILS_H

#include <functional>
#include <QMessageBox>

namespace Utils {

    void executeIfKDE(std::function<void()> onKDEFunc, std::function<void()> elsewhereFunc = []{});

    QMessageBox* createMessageBox(QWidget* parent = nullptr, const QString text = "", QMessageBox::Icon icon = QMessageBox::Icon::Information);

}

#endif // UTILS_H
