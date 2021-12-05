#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "MyListModel.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    MyListModel myList;
    engine.rootContext()->setContextProperty("MyModel", &myList);

    engine.load("qrc:/main.qml");

    return app.exec();
}
