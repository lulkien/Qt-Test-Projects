#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "SearchEngine.h"
#include "Constants.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

#if 0
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
#endif

    engine.rootContext()->setContextProperty("KConstant", &Constant::instance());
    engine.rootContext()->setContextProperty("SearchEngine", &SearchEngine::instance());

    const QString url("qrc:/qml/main.qml");
    engine.load(url);

    return app.exec();
}
