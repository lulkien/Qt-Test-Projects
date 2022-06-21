#ifndef SEARCHDEAMON_H
#define SEARCHDEAMON_H

#include <QObject>
#include <QThread>
#include <QByteArray>

class SearchDeamon : public QObject
{
    Q_OBJECT
public:
    enum SearchStatus {
        EndSearch = 0,
        Searching = 1,
        Querying = 2,
    };
    enum DatabaseStatus {
        Updating = 0,
        Updated,
    };

    SearchDeamon();
    ~SearchDeamon();

public slots:
    void reqUpdateDatabase();
    void onFinishedUpdateDatabase();


private:    // methods
    // initialize
    void initialize();

    // update database
    void            updateDatabase();
    bool            isDatabaseUpdated();

    // crypto graphic
    QByteArray      getSHA256(const QString &fileName);

private:    // properties
    // Crypto graphic
    QByteArray      mDatabaseSHA256;

    // threads
    QThread         mUpdateWorker;
    //    QThread         mQueryThread;

    // update new database
    int             mUpdateRequestPending;
    DatabaseStatus  mDatabaseStatus;
    SearchStatus    mSearchStatus;
    bool            mMustReplaceDB;

signals:
    void finishedUpdateDatabase();

};

#endif // SEARCHDEAMON_H
