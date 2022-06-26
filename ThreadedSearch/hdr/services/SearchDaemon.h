#ifndef SEARCHDEAMON_H
#define SEARCHDEAMON_H

#include <QObject>
#include <QMutex>
#include <QByteArray>
#include <QSqlDatabase>
#include <QString>

#define SEARCHD SearchDeamon::instance()

class SearchDeamon : public QObject
{
    Q_OBJECT
public:
    enum SearchStatus {
        Idle = 0,
        Query,
        Exit = 99,  // will not be used
    };
    Q_ENUM(SearchStatus)
    enum DatabaseUpdateStatus {
        Ready = 0,
        Updating,
    };
    Q_ENUM(DatabaseUpdateStatus)

    static SearchDeamon &instance();
    ~SearchDeamon();

public slots:
    void requestUpdateDatabase();
    void requestQuery(const QString &input);
    void onFinishUpdateDatabase();
    void onQueryFinished();


private:    // methods
    SearchDeamon();
    SearchDeamon(const SearchDeamon &other) = delete;
    void operator =(const SearchDeamon &other) = delete;
    // initialize
    void initialize();

    // update database
    void            startUpdateDatabase();
    void            doUpdateDatabase();
    bool            isDatabaseUpdated();
    void            replaceCurrentSearchDB();

    // modify database
    void            createSearchItemFrom(QSqlDatabase &db, const QString &table_name);
    void            insertItemIntoDB(QSqlDatabase &db, const QSqlRecord &record, const QString &table_name);
    QString         getUppermenu(QSqlDatabase &db, const int &index, const QString &defaultUpperMenu = "");

    // query
    void            startQuery(const QString &input);
    void            queryFromRelatedField(QSqlDatabase &db, QString input);

    // crypto graphic
    QByteArray      getSHA256(const QString &fileName);

private:    // properties
    // static
    static QMutex mLock;
    // Crypto graphic
    QByteArray      mDatabaseSHA256;

    // database
    QSqlDatabase    mUpdateDB;
    QSqlDatabase    mSearchDB;
    const QString mMakeTableCmd = QString("CREATE TABLE IF NOT EXISTS SEARCH_TABLE ("
                                          "idx INT, "
                                          "data TEXT, "
                                          "from_table TEXT, "
                                          "parent TEXT, "
                                          "support INT, "
                                          "related TEXT)");

    // update new database
    int                     mUpdateRequestPending;
    DatabaseUpdateStatus    mDatabaseStatus;
    SearchStatus            mSearchStatus;
    bool                    mNeedReplaceDatabase;
    bool                    mNeedReSearch;

signals:
    void finishUpdateDatabase();
    void queryFinished();

};

class Utilities
{
public:
    Utilities() {}
    ~Utilities() {}
    static QString getRelatedString(QString text);
};

#endif // SEARCHDEAMON_H
