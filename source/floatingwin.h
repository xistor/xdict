#ifndef FLOATINGWIN_H
#define FLOATINGWIN_H

#include <QObject>

class FloatingWin : public QObject
{
    Q_OBJECT
public:
    explicit FloatingWin(QObject *parent = nullptr);

    void handleSelectedTranslate(QString result);
signals:

};

#endif // FLOATINGWIN_H
