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

public slots:
    void doWork(const QString &from, const QString &to, const QString &word);

signals:
    void resultReady(const QString &result);

private:

    BaiduTranslate *_baiduTranslate;
};


class Translator : public QObject
{
    Q_OBJECT
public:

    Translator(QObject *parent = nullptr);


public slots:
    void handleResults(const QString &);

signals:
    void translate(const QString &from, const QString &to, const QString &word);
    void translateResult(const QString &result);

private:
    QThread _workerThread;


};

#endif // TRANSLATOR_H
