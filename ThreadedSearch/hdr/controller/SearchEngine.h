#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <QObject>
#include <QMutex>
#include <QString>
#include <QByteArray>
#include <QSqlDatabase>
#include <SearchDaemon.h>

class SearchEngine : public QObject
{
    Q_OBJECT
public:
    static SearchEngine *getInstance();
    ~SearchEngine();

public slots:
    void testFunction();

private:
    // static properties
    static QMutex mLock;
    static SearchEngine* mInstance;
    const QString CREATE_TABLE_CMD =    "CREATE TABLE IF NOT EXISTS SEARCH_TABLE "
                                        "(idx INT, "
                                        "table INT, "
                                        "content TEXT, "
                                        "keyword TEXT)";

    // Services
    SearchDeamon    mSearchDaemon;

    // normal properties
    QByteArray      mDatabaseSHA256;
    QString         mDatabaseConnection;
    QSqlDatabase    mDatabase;

private:
    // initialize
    explicit SearchEngine(QObject *parent = nullptr);
    void initData();

    // Crypto Graphic
    bool checkDatabaseUpdated();
    QByteArray getSHA256(const QString& fileName);
signals:

};

#endif // SEARCHENGINE_H
