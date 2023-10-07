#ifndef BAIDUTRANSLATE_H
#define BAIDUTRANSLATE_H

#include <QObject>
#include <QString>
#include <QEventLoop>
#include <QTimer>
#include <QMap>

class QNetworkAccessManager;
class QNetworkReply;


class BaiduTranslate:public QObject
{
public:
    BaiduTranslate(const BaiduTranslate& bai) = delete;
    BaiduTranslate& operator==(const BaiduTranslate& bai) = delete;

    static BaiduTranslate& getInstance()
    {
        static BaiduTranslate baiduTranslate;
        return baiduTranslate;
    }

    QString langDetect(const QString &word);
    QString translate(const QString &src, const QString &dst, const QString &word);

    QMap<QString, QString> langMap = {{"english", "en"}, {"chinese", "zh"}, {"auto", "auto"}};

private:
    BaiduTranslate();

    QString getSign(QString query);

    QString _gtk;
    QTimer _timer;
    QString _token;
    QEventLoop _loop;
    QNetworkReply *_reply;
    QNetworkAccessManager *_netManager;
};

#endif // BAIDUTRANSLATE_H
