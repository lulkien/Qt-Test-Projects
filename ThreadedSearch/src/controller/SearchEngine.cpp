#include "SearchEngine.h"
#include "Constants.h"
#include "Defines.h"
#include <QMutexLocker>
#include <QFile>
#include "SearchDaemon.h"

QMutex SearchEngine::mLock;

SearchEngine &SearchEngine::instance()
{
    QMutexLocker lock5er(&mLock);
    static SearchEngine engine;
    return engine;
}

SearchEngine::~SearchEngine()
{
}

void SearchEngine::testFunction()
{
    LOG;
    SearchDeamon::instance().requestUpdateDatabase();
}

SearchEngine::SearchEngine()
{
    initData();
}

void SearchEngine::initData()
{
    LOG;
    SearchDeamon::instance().requestUpdateDatabase();
}
