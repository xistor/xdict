#ifndef TRANSLATOR_H
#define TRANSLATOR_H
#include <QObject>
#include <QString>
#include <QThread>

#include "baidutranslate.h"

class QueryWorker : public QObject
{
    Q_OBJECT
public:
    QueryWorker();
    QString langDetect(const QString &word){ return _baiduTranslate->langDetect(word);}

public slots:
    void doWork(const QString &from, const QString &to, const QString &word);

signals:
    void resultReady(const QString &result);

private:    BaiduTranslate *_baiduTranslate;
};


class Translator : public QObject
{
    Q_OBJECT
public:
    enum TextSrc{
        TEXT_INPUT_BOX,
        CURSOR_SELECTED,
        UNKNOWN
    };
    Q_ENUM(TextSrc)

    Translator(QObject *parent = nullptr);
    void autoTranslate(const QString &word);
    void translateSelected(const QString &word);
    Q_INVOKABLE void translateText(const QString &word, TextSrc ts);

public slots:
    void handleResults(const QString &);

signals:
    void translate(const QString &from, const QString &to, const QString &word);
    void translateResult(const QString &result, TextSrc ts = CURSOR_SELECTED);

private:
    QueryWorker *_worker;
    QThread _workerThread;
    TextSrc _textSrc;
    QString _from;  // src lang
    QString _to;    // target lang


};

#endif // TRANSLATOR_H
