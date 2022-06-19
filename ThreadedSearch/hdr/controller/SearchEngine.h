#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <QObject>
#include <QMutex>
#include <QString>
#include <QByteArray>

class SearchEngine : public QObject
{
    Q_OBJECT
public:
    static SearchEngine *getInstance();
    virtual ~SearchEngine();

public slots:
    bool startCrawler();

private:
    // static properties
    static QMutex mLock;
    static SearchEngine* mInstance;
    const QString CREATE_TABLE_CMD =    "CREATE TABLE IF NOT EXISTS SEARCH_TABLE "
                                        "(idx INT, "
                                        "name TEXT, "
                                        "no_space TEXT, "
                                        "no_symbol TEXT, "
                                        "letter_only TEXT, "
                                        "abbreviation TEXT)";

    // normal properties
    QByteArray mDatabaseHash;

    // methods
    explicit SearchEngine(QObject *parent = nullptr);
    void initData();
    bool checkDatabaseUpdated();
    QByteArray getSHA256(const QString& fileName);
signals:

};

#endif // SEARCHENGINE_H
