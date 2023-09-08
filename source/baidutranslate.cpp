#include <QNetworkAccessManager>
#include <QtNetwork>
#include <QDebug>
#include <openssl/md5.h>
#include <QtGlobal>
#include "baidutranslate.h"

BaiduTranslate::BaiduTranslate()
{
    _netManager = new QNetworkAccessManager();
}


QString BaiduTranslate::langDetect(QString word)
{
    QUrlQuery data;
    data.addQueryItem("query", word);
    QNetworkRequest request;
    request.setUrl(QUrl("https://fanyi.baidu.com/langdetect"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) "
                                                        "Chrome/51.0.2704.103 Safari/537.36");

    _reply = _netManager->post(request, data.toString(QUrl::FullyEncoded).replace("+", "%2B").toUtf8());
    connect(_reply, &QNetworkReply::finished, &_loop, &QEventLoop::quit);
    _loop.exec();
    QJsonDocument doc = QJsonDocument::fromJson(_reply->readAll());
    qDebug() << "langDetect reply: " << doc;
    QJsonObject obj = doc.object();
    if (obj["error"].toInt() == 0)
    {
        return obj["lan"].toString();
    }
    _reply->deleteLater();
    return QString();
}




QString BaiduTranslate::translate(const QString &src, const QString &dst, const QString &word)
{

    QSettings settings("settings.ini", QSettings::IniFormat);
    QString appId = settings.value("appID").toString();
    QString secretKey = settings.value("secretKey").toString();
    QString url = settings.value("baiduUrl").toString();

    qInfo() << "appId" << appId;
    int a = rand();

    QString salt = QString::number(a);
    QString ss = appId + word + salt + secretKey;
    QString sign = QString(QCryptographicHash::hash(ss.toUtf8(),QCryptographicHash::Md5).toHex());


    QUrlQuery data;
    data.addQueryItem("appid", appId);
    data.addQueryItem("q", word);
    data.addQueryItem("from", langMap[src]);
    data.addQueryItem("to", langMap[dst]);
    data.addQueryItem("salt", salt);
    data.addQueryItem("sign", sign);
    qDebug() << data.toString();


    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) "
                                                        "Chrome/51.0.2704.103 Safari/537.36");


    _reply = _netManager->post(request, data.toString(QUrl::FullyEncoded).replace(" ", "%20").replace("+", "%2B").toUtf8());
    connect(_reply, &QNetworkReply::finished, &_loop, &QEventLoop::quit);
    _loop.exec();
    QJsonDocument doc = QJsonDocument::fromJson(_reply->readAll());
    qDebug() << "translate reply: " << doc;

    QJsonObject obj = doc.object();

    QString result;

    for(auto line : obj["trans_result"].toArray()) {
        result += line.toObject()["dst"].toString();
    }

    qDebug() << result;
    return result;
}

