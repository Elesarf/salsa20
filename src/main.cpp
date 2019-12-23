#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <json_parser.h>
#include <data_model.h>

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QList<data_model> l;
    l.append(data_model("one", "some", "somePassword"));
    l.append(data_model("two", "some", "somePassword"));
    l.append(data_model("tree", "some", "somePassword"));

    json_parser::save("./data.json", l);

    engine.load(QUrl("qrc:/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::quit, &app, &QGuiApplication::quit);
    return app.exec();
}
