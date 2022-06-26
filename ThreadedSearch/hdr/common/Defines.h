#ifndef DEFINES_H
#define DEFINES_H

#include <QDebug>
#include <QString>

#define LOG                         qDebug().noquote() << "[" << __FUNCTION__ << "][" << __LINE__ << "]"

// database path
#define SOURCE_DB_PATH              "/drive/HDD_1TB/Working/etc/database.db"
#define TMP_DB_PATH                 "/drive/HDD_1TB/Working/etc/tmp_database.db"
#define FINAL_DB_PATH               "/drive/HDD_1TB/Working/etc/final_database.db"

#define KEY_SEPARATOR               "#"

#endif // DEFINES_H
