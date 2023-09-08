

#include <QTcpSocket>

#include "blockingqueue.h"

#include "queryworker.h"




void QueryWorker::stop(){
    _query_queue.put({"","",""});
    _running = false;
}

void QueryWorker::set_srv(const QString& srv_addr, const uint16_t srv_port) {
    _srv_addr = srv_addr;
    _srv_port = srv_port;

}

void QueryWorker::query(const QString &from, const QString &to, const QString &words) {
    qInfo() << from << " " << to << " " << words << "\n";
    _query_queue.put({from, to, words});
}

void QueryWorker::run(){
    int readN;
    int nRetry = 0;

    _socket = new QTcpSocket();

    qInfo() << "Connecting to " << _srv_addr << "port " << _srv_port;
    _socket->connectToHost(QHostAddress(_srv_addr), _srv_port);

    if(_socket->waitForConnected(3000))
    {
        qDebug() << "Connected!";
    }

    while(_running) {
        qInfo() << "take \n" ;
        auto q = _query_queue.take();

        QJsonObject s = q.toJson();
        qInfo() << "query \n";

//        _socket->write(, s.size());
//        _socket->waitForBytesWritten();
//        qInfo() << "send " << QString(s.c_str()) << "\n";

        _socket->waitForReadyRead();
        readN =_socket->read(_buffer, SOCKET_BUFSIZE);

        if(readN) {
            _buffer[readN] = '\0';

            qInfo() << "response " << _buffer;
            ResponseMsg resMsg(_buffer);

//            emit queryResult(resMsg.dst);
        }

    }
    delete _socket;
    _socket = nullptr;
    qInfo() << "stop \n";
}

//void QueryWorker::queryResult(QString res) {
//    qInfo() << "QueryWorker::queryResult " << res;
//}

void QueryWorker::test() {
    qInfo() << "QueryWorker::test ";
}

QueryWorker::~QueryWorker(){
    if(_running){
        _running = false;
    }

    if(_socket)
        delete _socket;
}





