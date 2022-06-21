#include "SearchDaemon.h"
#include "Constants.h"
#include <QCryptographicHash>
#include <QtConcurrent>
#include <QFile>

SearchDeamon::SearchDeamon()
    : mDatabaseSHA256           { "" }
    , mUpdateRequestPending     { 0 }
    , mDatabaseStatus           { Updated }
{

}

SearchDeamon::~SearchDeamon()
{

}

void SearchDeamon::reqUpdateDatabase()
{
    LOG;
    mUpdateRequestPending++;
    LOG << "mUpdateRequestPending:" << mUpdateRequestPending << " | mUpdatingDatabase" << mDatabaseStatus;
    if (mDatabaseStatus != Updating)
    {
        updateDatabase();
    }
}

void SearchDeamon::onFinishedUpdateDatabase()
{
    LOG << "mUpdateRequestPending:" << mUpdateRequestPending << " | mUpdatingDatabase" << mDatabaseStatus;
    if (mUpdateRequestPending > 0 && mDatabaseStatus != Updating)
    {
        LOG << "Continue update!";
        updateDatabase();
    }
    else
    {
        if (mSearchStatus == Querying)
        {
            // wait until query finished then update then re-seach
        }
        else if (mSearchStatus == Searching)
        {
            // update and re-search
        }
        else
        {
            // just update
        }
    }
}

void SearchDeamon::initialize()
{
}

void SearchDeamon::updateDatabase()
{
    LOG << QThread::currentThreadId();
    mUpdateRequestPending = 0;  // clear all pending request and update
    if (isDatabaseUpdated() == false) return;
    QtConcurrent::run([&](){
        mDatabaseStatus = Updating;
        LOG << QThread::currentThreadId();
        LOG << "Start sleep";
        for (int i = 0; i < 3; i++)
        {
            LOG << i;
            QThread::sleep(1);
        }
        LOG << "End sleep";
        mDatabaseStatus = Updated;
        onFinishedUpdateDatabase();
    });
}

bool SearchDeamon::isDatabaseUpdated()
{
    LOG << "Old SHA256:                  " << mDatabaseSHA256;
    QByteArray newHash = getSHA256(DATABASE_PATH);
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

