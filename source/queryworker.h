#ifndef QUERYWORKER_H
#define QUERYWORKER_H


#ifdef Data
#undef Data
#endif

#ifdef Status
#undef Status
#endif

#ifdef Bool
#undef Bool
#endif

#include <QThread>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>

#include "blockingqueue.h"



#define SOCKET_BUFSIZE 4096

// Query msg & Response msg

class QTcpSocket;
class QueryMsg {

public:
    QString from;
    QString to;
    QString words;

    QueryMsg(const QString& from, const QString& to, const QString& words )
        :from(from),
        to(to),
        words(words)
    {}


    QJsonObject toJson(){
        QJsonObject j;
        j["from"] = from;
        j["to"] = to;
        j["words"] = words;
        return j;
    }

};

class ResponseMsg {

public:
    QString error_code;
    QString error_msg;
    QString from;
    QString to;
    QString src;
    QString dst;

    ResponseMsg(QString response) : error_code{}
    {
        QJsonObject res_json;
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response.toUtf8());
        res_json = jsonResponse.object();


        if(res_json.contains("error_code")){
            error_code = res_json["error_code"].toString();
            error_msg = res_json["error_msg"].toString();
        } else {
            error_code.clear();
            from = res_json["from"].toString();
            to = res_json["to"].toString();
            src = res_json["trans_result"][0]["src"].toString();
            dst = res_json["trans_result"][0]["dst"].toString();
        }
    }
};



class QueryWorker : public QThread
{

public:

    QueryWorker(){};

    void stop();
    void set_srv(const QString& srv_addr, const uint16_t srv_port);
    void query(const QString &from, const QString &to, const QString &words);

    void test();
    ~QueryWorker();

protected:
    void run() override;

private:

    bool                        _running;
    QString                     _srv_addr;
    uint16_t                    _srv_port;
    QTcpSocket *                _socket;
    int                         _sockt_fd;
    char                        _buffer[SOCKET_BUFSIZE];
    xistor::BlockingQueue<QueryMsg>     _query_queue;

signals:
    void queryResult(QString res);

public slots:

};

#endif // QUERYWORKER_H
