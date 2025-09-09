#ifndef UTILS_H
#define UTILS_H

#include <functional>
#include <QMessageBox>

namespace Utils {

    void executeIfKDE(std::function<void()> onKDEFunc, std::function<void()> elsewhereFunc = []{});

    QMessageBox* createMessageBox(QWidget* parent = nullptr, QMessageBox::Icon icon = QMessageBox::Icon::Information, const QString text = "");
}

#endif // UTILS_H
