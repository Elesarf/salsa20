#include <QIcon>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "data_model_controller.h"
#include "view_model.h"
#include "version.h"

int main(int argc, char **argv)
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    app.setWindowIcon(QIcon(":/media/salsa.png"));

    qmlRegisterType<dataModelController>("com.ass.crypter", 1, 0, "CardController");
    qmlRegisterType<view_model>("com.ass.crypter", 1, 0, "ViewModel");
    qmlRegisterType<Version>("com.ass.crypter", 1, 0, "Version");

    engine.load(QUrl("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::quit, &app, &QGuiApplication::quit);
    return app.exec();
}
