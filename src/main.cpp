#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "data_model_controller.h"

#include "view_model.h"

int main(int argc, char **argv)
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<data_model_controller>("com.ass.crypter", 1, 0, "CardController");
    qmlRegisterType<view_model>("com.ass.crypter", 1, 0, "ViewModel");

    engine.load(QUrl("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::quit, &app, &QGuiApplication::quit);
    return app.exec();
}
