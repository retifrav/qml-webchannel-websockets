#include "backend.h"

Backend::Backend(QObject *parent) : QObject(parent)
{
    someProperty = "Break on through to the other side";
}

QString Backend::getSomeProperty()
{
    return someProperty;
}

void Backend::setSomeProperty(QString newValue)
{
    someProperty = newValue;
    emit somePropertyChanged(newValue);
}

QString Backend::changeText(QString newText)
{
    qDebug() << "invoked " << newText;
//    someProperty = "fuuu";
//    emit somePropertyChanged(newText);
    emit textNeedsToBeChanged(newText);
    return newText;
}
