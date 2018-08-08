/*
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext> // required for setting context property
#include "backend.h"
#include <QDebug>
*/

// Now: QApplication replaces QGuiApplication
// QQuickView replaces QQmlApplicationEngine

#include <QDebug>
#include "backend.h"
#include <QQuickView>
#include <QCoreApplication>
#include <QApplication>
#include <QQmlContext>
#include <QtQml/QQmlEngine>



int main(int argc, char *argv[])
{
    // initialisation
    //QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    QQuickView* viewer = new QQuickView;
    // load backend class
    MyBackend backend;
    viewer->rootContext()->setContextProperty("backend", &backend);
    //QObject::connect(&backend, SIGNAL(backend.textChanged("new Text")), engine.rootObjects()[0], );
    viewer->engine()->addImportPath("/home/moritz/qtProjects/qtControlsProject/qml");
    viewer->setSource(QUrl(QLatin1String("qrc:/main.qml")));
    if (viewer->rootObject() == nullptr)
        return -1;

    QQuickItem* item = viewer->rootObject();
    if(item == nullptr)
        qDebug() << "Es wurde kein Root-Objekt gefunden.";
    else
        backend.setRootObject(item);

    backend.initUI();
    viewer->show();
    return app.exec();
}
