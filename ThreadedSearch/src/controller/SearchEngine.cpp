#include "SearchEngine.h"
#include "Constants.h"
#include <QCryptographicHash>
#include <QMutexLocker>
#include <QFile>
#include <QtConcurrent>
#include <QFuture>
#include "SearchDaemon.h"

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

void SearchEngine::testFunction()
{
    LOG;
    emit SearchDeamon::instance().requestUpdateDatabase();
}

SearchEngine::SearchEngine(QObject *parent)
    : QObject               { parent }
    , mDatabaseSHA256       { QByteArray() }
    , mDatabaseConnection   { "" }
{
    initData();
}

void SearchEngine::initData()
{
    LOG;
}

bool SearchEngine::checkDatabaseUpdated()
{
    LOG << "Old hash:" << mDatabaseSHA256;
    QByteArray newHash = getSHA256(SOURCE_DB_PATH);
    if (!newHash.isEmpty())
    {
        if (newHash != mDatabaseSHA256)
        {
            mDatabaseSHA256 = newHash;
            LOG << "New hash:" << newHash;
            LOG << "Database updated!";
            return true;
        }
        else
        {
            LOG << "Database unchanged!";
            return false;
        }
    }
    LOG << "Cannot found the db -> use the old one!";
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
