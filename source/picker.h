#ifndef PICKER_H
#define PICKER_H

#include <QObject>
#include <QPoint>

class QClipboard;
class Picker : public QObject
{
    Q_OBJECT
public:
    explicit Picker(QObject *parent = nullptr);

    void onButtonPressed(int x, int y);
    void onButtonReleased(int x, int y);
    void onSelectedChanged();
    QPoint getTextPostion();

    Q_INVOKABLE void test();
private:
    QClipboard *clipboard;
    bool isPress;
    QPoint textPostion;

signals:
    void textSelected();
};

#endif // PICKER_H
