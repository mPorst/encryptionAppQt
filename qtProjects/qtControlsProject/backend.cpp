#include "backend.h"
#include "encrypting.h"
#include "fileHelper.h"
#include <Qt>
#include <string>
#include <iostream>
#include <QString>
#include <QDebug>

MyBackend::MyBackend(QObject *parent) : QObject(parent)
{

}

void MyBackend::encrypt(QString filename, QString key)
{
    std::string file = filename.toStdString().erase(0, 7);
    std::cout << file;
    encryptFile(file, key.toStdString());
    updateFilePreview(filename);
    //emit textChanged(changedText(filename));
}

QString MyBackend::changedText(QString fileName)
{
    //m_text = QString::fromStdString(fileText(fileName.toStdString()));
    //return  m_text;
}

void MyBackend::updateFilePreview(QString fileName)
{
    if(fileName.at(0) != '/')
        fileName.remove(0, 7);
    QString text = QString::fromStdString(fileText(fileName.toStdString()));
    QObject* mybox = rootObject->findChild<QObject*>("someTextArea");
    if(mybox == nullptr)
        qDebug() << "Object \"someTextArea\" not found -> nullptr. Can't change text property";
    else
        mybox->setProperty("text", text);
}

void MyBackend::setRootObject(QQuickItem* theRootObject)
{
    if(theRootObject == nullptr) {
        qDebug("BACKEND ERROR WHEN SETTING ROOT OBJECT: NULLPTR");
    }
    else {
        rootObject = theRootObject;
    }
}
