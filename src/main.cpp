#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "data_model.h"

#include "view_model.h"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    qmlRegisterType<card_type>("com.ass.crypter", 1, 0, "CardType");
    qmlRegisterType<card_model>("com.ass.crypter", 1, 0, "CardModel");
    qmlRegisterType<view_model>("com.ass.crypter", 1, 0, "ViewModel");

    engine.load(QUrl("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::quit, &app, &QGuiApplication::quit);
    return app.exec();
}
