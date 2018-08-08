#include "backend.h"
#include "encrypting.h"
#include "fileHelper.h"
#include <Qt>
#include <string>
#include <iostream>
#include <QString>
#include <QDebug>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QChartView>
#include <QBarSeries>
#include <algorithm>
#include <QVector>

MyBackend::MyBackend(QObject *parent) : QObject(parent)
{

}

void MyBackend::encrypt(QString filename, QString key)
{
    std::string file = filename.toStdString().erase(0, 7);
    std::cout << file;
    encryptFile(file, key.toStdString());
    updateFilePreview(filename);
    updateGraph(filename);
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

void MyBackend::fillBarSet(QList<int> data)
{
    /*
     * access barseries via Q_PROPERTY -> was not possible to get it via findChild<QObject*> (always returned nullpointer)
    */

        m_values.clear(); m_labels.clear(); m_max = 0; //reset values to re-evaluate for new data sets
        for(int i=0; i<data.size(); i++)
        {
            m_values.push_back(data.at(i));
            m_labels.push_back(QString::number(i));
        }
        // Determine largest element within m_values
        for(int i=0; i<m_values.size(); i++)
        {
           if(m_max < m_values.at(i).toInt())// this is safe as long as m_values contains only integers
               m_max = m_values.at(i).toInt();
        }

        emit valuesChanged();

            //barset->setProperty("values", data);
        /*QList<QObject*> objects = rootObject->findChildren<QObject*>();
        foreach (QObject* b, objects) {
            std::cout << b->objectName().toStdString() << std::endl;
        }*/
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

void MyBackend::updateGraph(QString filename)
{
    QList<int> list; std::vector<int> distribution;
    distribution = characterDistribution(filename.toStdString().erase(0, 7));
    for(unsigned int i=0; i<distribution.size(); i++) {
        list.push_back(distribution.at(i));
    }
    m_text = filename.remove(0, 7);
    emit textChanged();
    fillBarSet(list);
}


void MyBackend::initUI()
{
    m_text = "no file chosen";
    emit textChanged();
}
