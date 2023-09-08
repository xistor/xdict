#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include <QQmlContext>
#include <QSettings>

#include "picker.h"
#include "eventmonitor.h"
#include "translator.h"

int main(int argc, char *argv[])
{

    QGuiApplication app(argc, argv);



    QSettings::setDefaultFormat(QSettings::IniFormat);
    QGuiApplication::setApplicationName("XDict");

    QSettings settings("settings.ini", QSettings::IniFormat);

    qDebug() << QGuiApplication::applicationDirPath();
    Picker *picker = new Picker();

    Translator *tor = new Translator();
    app.setWindowIcon(QIcon(":/icon/app.png"));
    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();


    context->setContextProperty("picker", picker);
    context->setContextProperty("translator", tor);


    const QUrl url(u"qrc:/xdict/qml/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);



    // button
    QObject::connect(&EventMonitor::getInstance(), &EventMonitor::buttonPress, picker, &Picker::onButtonPressed, Qt::QueuedConnection);
    QObject::connect(&EventMonitor::getInstance(), &EventMonitor::buttonRelease, picker, &Picker::onButtonReleased, Qt::QueuedConnection);


    EventMonitor::getInstance().start();
    return app.exec();
}
