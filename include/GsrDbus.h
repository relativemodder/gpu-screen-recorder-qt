#ifndef GSRDBUS_H
#define GSRDBUS_H

#define SERVICE_NAME "com.github.relative.gpu-screen-recorder-qt"

#include <QObject>

class GsrDbus : public QObject
{
    Q_OBJECT
public:
    explicit GsrDbus(QObject *parent = nullptr);

public slots:
    void appear();
    void disappear();
    void toggleShow();

signals:
};

#endif // GSRDBUS_H
