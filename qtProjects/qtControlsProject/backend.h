#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <string>
#include <QQuickItem>

class MyBackend : public QObject
{
    Q_OBJECT

    Q_PROPERTY (QString fileText MEMBER m_text NOTIFY textChanged)
    Q_PROPERTY (QList<QVariant> graphValues MEMBER m_values NOTIFY valuesChanged)
    Q_PROPERTY (QStringList xLabels MEMBER m_labels NOTIFY valuesChanged)
    Q_PROPERTY (int yMax MEMBER m_max NOTIFY valuesChanged)

public:
    explicit MyBackend(QObject* parent = nullptr);
    void setRootObject(QQuickItem* theRootObject);

public slots:
    void encrypt(QString filename, QString key);
    void updateFilePreview(QString fileName);
    void fillBarSet(QList<int> data);
    QString changedText(QString filename);
    //bool isTextChanged();
    void updateGraph(QString filename);
    void initUI();


signals:
    void textChanged();
    void valuesChanged();

private:
    QQuickItem* rootObject;
    QString m_text;
    QList<QVariant> m_values;
    QStringList m_labels;
    int m_max = 0;
};

#endif // BACKEND_H
