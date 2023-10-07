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
    QGuiApplication::setApplicationName("XDict");

    QSettings settings("settings.ini", QSettings::IniFormat);

    Picker *picker = new Picker();
    Translator *translator = new Translator();

    app.setWindowIcon(QIcon(":/icon/app.png"));
    QQmlApplicationEngine engine;

    QQmlContext *context = engine.rootContext();


    context->setContextProperty("picker", picker);
    context->setContextProperty("translator", translator);
    qmlRegisterType<Translator>("Translator", 1, 0, "Translator");

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


    // text selected
    QObject::connect(picker, &Picker::textSelected, translator, &Translator::translateSelected, Qt::QueuedConnection);


    EventMonitor::getInstance().start();

    return app.exec();
}
