#include "SearchDaemon.h"
#include "Constants.h"
#include "Defines.h"
#include <QCryptographicHash>
#include <QtConcurrent>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QMutexLocker>

QMutex SearchDeamon::mLock;

SearchDeamon::SearchDeamon()
    : mDatabaseSHA256           { "" }
    , mUpdateRequestPending     { 0 }
    , mDatabaseStatus           { Ready }
    , mSearchStatus             { Idle }
    , mNeedReplaceDatabase      { false }
{
    LOG << "Init SearchD";
    initialize();
}

SearchDeamon &SearchDeamon::instance()
{
    QMutexLocker locker(&mLock);
    static SearchDeamon daemon;
    return daemon;
}

SearchDeamon::~SearchDeamon()
{
    LOG << "De-init SearchD";
}

void SearchDeamon::requestUpdateDatabase()
{
    mUpdateRequestPending++;
    LOG << "mUpdateRequestPending:" << mUpdateRequestPending << " | mDatabaseStatus: " << mDatabaseStatus;
    if (mDatabaseStatus != Updating)
    {
        startUpdateDatabase();
    }
}

void SearchDeamon::onFinishUpdateDatabase()
{
    LOG << QThread::currentThreadId() << "************************************************";
    if (mUpdateRequestPending != 0)
    {
        LOG << "Update again!";
        startUpdateDatabase();
    }
    else
    {
        if (mSearchStatus == Query)
        {
            // wait for searching done
            mNeedReplaceDatabase = true;
        }
        else
        {
            // just replace
            replaceCurrentSearchDB();
        }
        // Database ready
    }
}

void SearchDeamon::onQueryFinished()
{
    LOG;
    if (mNeedReplaceDatabase)
    {
        replaceCurrentSearchDB();
    }
}

void SearchDeamon::initialize()
{
    LOG << "Main thread: " << QThread::currentThreadId();
    connect(this, &SearchDeamon::finishUpdateDatabase   , this, &SearchDeamon::onFinishUpdateDatabase   , Qt::QueuedConnection);
    connect(this, &SearchDeamon::queryFinished          , this, &SearchDeamon::onQueryFinished          , Qt::AutoConnection);
}

void SearchDeamon::startUpdateDatabase()
{
    LOG << QThread::currentThreadId();
    mUpdateRequestPending = 0;  // clear all pending request and update
    if (isDatabaseUpdated() == false) return;
    QtConcurrent::run([&](){
        doUpdateDatabase();
        emit finishUpdateDatabase();
    });
}

void SearchDeamon::doUpdateDatabase()
{
    LOG << "Update thread: " << QThread::currentThreadId();
    mDatabaseStatus = Updating;
    QFile tmpDB(TMP_DB_PATH);
    if (tmpDB.exists())
    {
        LOG << "Remove old temporary DB";
        tmpDB.remove();
    }
    QFile::copy(SOURCE_DB_PATH, TMP_DB_PATH);
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(TMP_DB_PATH);
    if (database.open())
    {
        // do
        LOG << "Do update";
        database.exec("PRAGMA synchronous = OFF");
        database.exec("PRAGMA journal_mode = MEMORY");
        database.exec(mMakeTableCmd);
        createSearchItemFrom(database, "app");
        createSearchItemFrom(database, "CCVRSystemSubItems");
        database.close();
    }
    else
    {
        LOG << database.lastError().text();
    }
}

bool SearchDeamon::isDatabaseUpdated()
{
    LOG << "Old SHA256:                  " << mDatabaseSHA256;
    QByteArray newHash = getSHA256(SOURCE_DB_PATH);
    if (!newHash.isEmpty())
    {
        if (newHash != mDatabaseSHA256)
        {
            mDatabaseSHA256 = newHash;
            LOG << "Database updated! New SHA256:" << newHash << "";
            return true;
        }
        else
        {
            LOG << "Database NOT update!";
            return false;
        }
    }
    LOG << "Cannot found the db -> use the old one!";
    return false;
}

void SearchDeamon::replaceCurrentSearchDB()
{
    LOG;
    QFile finalDB(FINAL_DB_PATH);
    if (finalDB.exists())
    {
        LOG << "Remove old final DB";
        finalDB.remove();
    }
    QFile::copy(TMP_DB_PATH, FINAL_DB_PATH);
    mDatabaseStatus = Ready;
}

void SearchDeamon::createSearchItemFrom(QSqlDatabase &db, const QString &table_name)
{
    LOG << "From Table: " << table_name;
    QSqlQueryModel model;
    model.setQuery(QString("SELECT * FROM \"%1\" WHERE dynamicmenu = 1").arg(table_name), db);
    while (model.canFetchMore()) {
        model.fetchMore();
    }
    int modelSize = model.rowCount();
    LOG << "COUNT: " << modelSize;
    if (modelSize == 0)
        return;

    for (int i = 0; i < modelSize; i++)
    {
        QSqlRecord rec = model.record(i);
        insertItemIntoDB(db, rec, table_name);
    }
}

void SearchDeamon::insertItemIntoDB(QSqlDatabase &db, const QSqlRecord &record, const QString &table_name)
{
    int index = record.value("idx").toInt();
    QString data = record.value("us_eng").toString();

    if (data.isEmpty() || data == "N/A")
        return;

    int support = record.value("support").toInt();
    QString related = Utilities::getRelatedString(data);
    QString parent = getUppermenu(db, record.value("uppermenuidx").toInt(),
                                  record.value("uppermenu").toString());

    QString command = QString("INSERT INTO SEARCH_TABLE (idx, data, from_table, parent, support, related) "
                              "VALUES (:idx, :data, :from_table, :parent, :support, :related)");
    QSqlQuery query(db);
    if (query.prepare(command))
    {
        query.bindValue(":idx"          , index);
        query.bindValue(":data"         , data);
        query.bindValue(":from_table"   , table_name);
        query.bindValue(":parent"       , parent);
        query.bindValue(":support"      , support);
        query.bindValue(":related"      , related);
        query.exec();
    }
    else
    {
        LOG << query.lastError().text();
        return;
    }
}

QString SearchDeamon::getUppermenu(QSqlDatabase &db, const int &index, const QString &defaultUpperMenu)
{
    QSqlQuery query = db.exec(QString("SELECT * FROM app WHERE idx = %1").arg(index));
    QString ret = defaultUpperMenu;
    if (query.next())
    {
        ret = query.record().value("us_eng").toString();
        if (ret.isEmpty()) ret = defaultUpperMenu;
    }
//    LOG << ret.trimmed();
    return ret.trimmed();
}

QByteArray SearchDeamon::getSHA256(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QFile::ReadOnly))
    {
        QCryptographicHash sha256(QCryptographicHash::Sha256);
        if (sha256.addData(&file))
        {
            return sha256.result().toHex();
        }
    }
    return QByteArray();
}

//##################################################################################################################//

QString Utilities::getRelatedString(QString text)
{
    text = text.trimmed();
    QString no_space = "";
    QString no_symbol = "";
    QString letter_only = "";
    QString abbreviated = "";
    for (int i = 0; i < text.size(); i++)
    {
        QChar _c = text.at(i);
        if (!_c.isSpace())
            no_space.append(_c);
        if (_c.isLetterOrNumber() || _c.isSpace())
            no_symbol.append(_c);
        if (_c.isLetter())
            letter_only.append(_c);
    }
    QString ret = "";
    ret.append(no_space);
    if (no_symbol != no_space)
    {
        ret.append(KEY_SEPARATOR).append(no_symbol);
        if (letter_only != no_space && letter_only != no_symbol)
        {
            ret.append(KEY_SEPARATOR).append(letter_only);
        }
    }
    if (!abbreviated.isEmpty())
    {
        ret.append(KEY_SEPARATOR).append(abbreviated);
    }
//    LOG << ret;
    return ret;
}

