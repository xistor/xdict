#include "xcontroller.h"

XController::XController(QObject *parent)
    : QObject{parent}
{
//     _queryWorker = nullptr;
}

//void XController::connectServer(const QString& srv_addr, const uint16_t srv_port)
//{
//     if(_queryWorker == nullptr) {
//         _queryWorker = new QueryWorker(srv_addr, srv_port);
//     }

//     _queryWorker->start();
//}

//void XController::query(const QString &from, const QString &to, const QString& words)
//{
//     _queryWorker->query(from, to, words);
//}

//void XController::onQueryReturn(QString& res)
//{
//}

