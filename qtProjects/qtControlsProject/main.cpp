#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext> // required for setting context property
#include "backend.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    // initialisation
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    // load backend class
    MyBackend backend;
    engine.rootContext()->setContextProperty("backend", &backend);
    //QObject::connect(&backend, SIGNAL(backend.textChanged("new Text")), engine.rootObjects()[0], );
    engine.addImportPath("/home/moritz/qtProjects/qtControlsProject/qml");
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QObject* item = engine.rootObjects().first();
    backend.setRootObject(item);
    if(item == nullptr)
    {
        qDebug() << "Es wurde kein Root-Objekt gefunden. Beende QT.";
    }
    qDebug() << item->objectName();

    return app.exec();
}
