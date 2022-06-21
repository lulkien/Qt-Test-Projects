#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QDebug>
#include <QString>

#define LOG                         qDebug().noquote() << "[" << __FUNCTION__ << "][" << __LINE__ << "]"
#define DATABASE_PATH               "/drive/HDD_1TB/Working/etc/database.db"

#define STRING_SEPARATOR            "<[$]>"

#define DB_UPDATING                 true
#define DB_UPDATED                  false


#endif //CONSTANTS_H
