#include <QGuiApplication>
#include <QQmlApplicationEngine>

constexpr char c_nonce[] = "99990001";

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.load(QUrl("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::quit, &app, &QGuiApplication::quit);
    return app.exec();
}
