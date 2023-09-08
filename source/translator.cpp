#include "translator.h"

#include <QDebug>
#include <QThread>

Translator::Translator(QObject *parent)
    : QObject{parent}
{
    QueryWorker *worker = new QueryWorker;
    worker->moveToThread(&_workerThread);
    connect(&_workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &Translator::translate, worker, &QueryWorker::doWork);
    connect(worker, &QueryWorker::resultReady, this, &Translator::handleResults);
    _workerThread.start();

}


void Translator::handleResults(const QString & res)
{
    qDebug() << "Translator::handleResults " << res;

    emit translateResult(res);
}

QueryWorker::QueryWorker(){

}

void QueryWorker::doWork(const QString &from, const QString &to, const QString &word) {
    /* ... here is the expensive or blocking operation ... */
    qInfo() << from << to << word;
    _baiduTranslate = &BaiduTranslate::getInstance();
    emit resultReady(_baiduTranslate->translate(from, to, word));
}
