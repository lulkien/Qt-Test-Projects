#include "SearchEngine.h"
#include "Constants.h"
#include "Defines.h"
#include "SearchDaemon.h"
#include <QMutexLocker>
#include <QFile>
#include <QQmlEngine>

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

void SearchEngine::search(QString input, bool forced)
{
    input = input.trimmed();
    if (input.isEmpty())
    {
        LOG << "Empty input!";
        return;
    }
    if (input == mLastInput && !forced)
    {
        LOG << "Match with last input + Unforce";
        return;
    }
    mLastInput = input;
    LOG << "Input: " << mLastInput;
    SearchDeamon::instance().requestQuery(mLastInput);
}

SearchEngine::SearchEngine()
    : mLastInput            { "" }
    , mCurrentFocusingItem  { -1 }
{
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    initData();
}

void SearchEngine::initData()
{
    LOG;
    SearchDeamon::instance().requestUpdateDatabase();
}
