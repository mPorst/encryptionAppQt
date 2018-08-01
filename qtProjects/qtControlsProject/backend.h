#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <string>

class MyBackend : public QObject
{
    Q_OBJECT

    //Q_PROPERTY (QString fileText MEMBER m_text NOTIFY textChanged)

public:
    explicit MyBackend(QObject *parent = nullptr);
    void setRootObject(QObject* theRootObject);

public slots:
    void encrypt(QString filename, QString key);
    void updateFilePreview(QString fileName);
    QString changedText(QString filename);
    //bool isTextChanged();

signals:
    void textChanged(QString newText);

private:
    QObject* rootObject;
};

#endif // BACKEND_H
