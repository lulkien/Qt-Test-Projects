#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <QObject>
#include <QMutex>
#include <QString>
#include <QByteArray>

class SearchEngine : public QObject
{
    Q_OBJECT
public:
    static SearchEngine &instance();
    virtual ~SearchEngine();

public slots:
    void testFunction();

private:
    // static properties
    static QMutex mLock;

    // normal properties

private:
    // initialize
    SearchEngine();
    void initData();

signals:

};

#endif // SEARCHENGINE_H
