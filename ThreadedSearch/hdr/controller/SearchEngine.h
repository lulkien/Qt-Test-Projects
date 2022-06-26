#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <QObject>
#include <QMutex>
#include <QString>
#include <QByteArray>
#include <QtQml/qqml.h>

class SearchEngine : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    static SearchEngine &instance();
    virtual ~SearchEngine();

    QString         lastInput() const { return mLastInput; }

public slots:
    void testFunction();
    void    search(QString input, bool forced = false);
    bool    isEmptyInput() { return mLastInput.isEmpty(); }

private:
    // static properties
    static QMutex       mLock;

    // normal properties
    QString             mLastInput;
    int                 mCurrentFocusingItem;

private:
    // initialize
    SearchEngine();
    void initData();

signals:

};

#endif // SEARCHENGINE_H
