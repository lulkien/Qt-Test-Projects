#include "SearchEngine.h"
#include "Constants.h"
#include <QCryptographicHash>
#include <QMutexLocker>
#include <QFile>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>

SearchEngine* SearchEngine::mInstance = nullptr;
QMutex SearchEngine::mLock;

SearchEngine *SearchEngine::getInstance()
{
    QMutexLocker lock5er(&mLock);
    if (nullptr == mInstance)
    {
        mInstance = new SearchEngine();
    }
    return mInstance;
}

SearchEngine::~SearchEngine()
{
}

bool SearchEngine::startCrawler()
{
    qout << CREATE_TABLE_CMD;
    bool isUpdated = checkDatabaseUpdated();
    if (!isUpdated)
    {
        qout << "Database unchanged -> ignore!";
        return false;
    }
    return isUpdated;
}

SearchEngine::SearchEngine(QObject *parent)
    : QObject               { parent }
    , mDatabaseHash         { QByteArray() }
{
    initData();
}

void SearchEngine::initData()
{
    QFuture<void> initThread = QtConcurrent::run([=](){
        mDatabaseHash = getSHA256(DATABASE_PATH);
    });
}

bool SearchEngine::checkDatabaseUpdated()
{
    qout << "Old hash:" << mDatabaseHash;
    QByteArray newHash = getSHA256(DATABASE_PATH);
    if (!newHash.isEmpty())
    {
        if (newHash != mDatabaseHash)
        {
            mDatabaseHash = newHash;
            qout << "New hash:" << newHash;
            qout << "Database updated!";
            return true;
        }
        else
        {
            qout << "Database unchanged!";
            return false;
        }
    }
    qout << "Cannot found the db -> use the old one!";
    return false;
}

QByteArray SearchEngine::getSHA256(const QString &fileName)
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
