#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QDebug>

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString someProperty READ getSomeProperty WRITE setSomeProperty NOTIFY somePropertyChanged)

public:
    explicit Backend(QObject *parent = nullptr);
    QString getSomeProperty();

signals:
    void someSignal(QString message);
    void textNeedsToBeChanged(QString newText);
    void somePropertyChanged(QString newValue);

public slots:
    void setSomeProperty(QString newValue);
    QString changeText(QString newText);

private:
    QString someProperty;
};

#endif // BACKEND_H
