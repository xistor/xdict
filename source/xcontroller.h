#ifndef XCONTROLLER_H
#define XCONTROLLER_H

#include <QObject>

//#include "blockingqueue.h"
//#include "queryworker.h"


class XController : public QObject
{
    Q_OBJECT
public:
    explicit XController(QObject *parent = nullptr);

private:
//    QueryWorker *_queryWorker;
//    xistor::BlockingQueue<ResponseMsg> _responseQueue;

signals:

};

#endif // XCONTROLLER_H
