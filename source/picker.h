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
    Q_INVOKABLE QPoint getTextPostion();

private:
    QClipboard *clipboard;
    bool isPress;
    QPoint textPostion;

signals:
    void textSelected(const QString &selectedText);
};

#endif // PICKER_H
