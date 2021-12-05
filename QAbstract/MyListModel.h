#ifndef MYLISTMODEL_H
#define MYLISTMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QByteArray>
#include <QVariant>
#include <QList>
#include <QString>
#include "MyItem.h"

class MyListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum ItemRoles {
        Data = Qt::UserRole + 1,
        Color,
        TextColor,
    };
    MyListModel();
    virtual ~MyListModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;     // must override this function
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override; // must override this function

public slots:
    void addLastItem(QString _data, QString _color, QString _textColor);
    void addItemAt(int idx, QString _data, QString _color, QString _textColor);
    void changeItemAt(int idx, QString _data, QString _color, QString _textColor);
    void deleteItem(int idx);

protected:
    QHash<int, QByteArray> roleNames() const override;  // must override this function
private:
    QList<MyItem *> m_listItems;
};

#endif
