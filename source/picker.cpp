#include <QGuiApplication>
#include <QDebug>
#include <QClipboard>
#include <QString>
#include "picker.h"


Picker::Picker(QObject *parent)
    : QObject{parent}
{
    isPress = false;
    clipboard = QGuiApplication::clipboard();
    connect(clipboard, &QClipboard::selectionChanged, this, &Picker::onSelectedChanged);
}

void Picker::onButtonPressed(int x, int y){
    qDebug() <<"Picker::onButtonPressed (" << x << "," << y << ")";
    isPress = true;
}

void Picker::onButtonReleased(int x, int y){
    qDebug() <<"Picker::onButtonReleased (" << x << "," << y << ")";
    textPostion.setX(x);
    textPostion.setY(y);
    isPress = false;

}

void Picker::onSelectedChanged(){
    qDebug() <<"Picker::onSelectedChanged";
    QString text;
    if(!isPress) {
        text = clipboard->text(QClipboard::Selection);
        qDebug() << text;
        emit textSelected(text);
    }
}

QPoint Picker::getTextPostion(){
    return textPostion;
}
