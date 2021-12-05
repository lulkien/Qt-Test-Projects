#include "MyListModel.h"
#include <QDebug>

#define FUNC_NAME qDebug() << "[" << __FUNCTION__ << "]";

MyListModel::MyListModel() {}

MyListModel::~MyListModel()
{
    for (auto item : m_listItems)
    {
        delete item;
        item = nullptr;
    }
}

int MyListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_listItems.count();
}

QVariant MyListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= rowCount())
        return QVariant();
    MyItem *item = m_listItems.at(index.row());
    switch (role) {
    case Data:
        return item->getData();
    case Color:
        return item->getColor();
    case TextColor:
        return item->getTextColor();
    default:
        return QVariant();
    }
}

void MyListModel::addLastItem(QString _data, QString _color, QString _textColor)
{
    FUNC_NAME
    MyItem *newItem = new MyItem(_data, _color, _textColor);
    beginInsertRows(QModelIndex(), rowCount(), rowCount());  // add 1 item to tail of list => begin = rowCount & end = rowCount
    m_listItems.append(newItem);
    endInsertRows();
}

void MyListModel::addItemAt(int idx, QString _data, QString _color, QString _textColor)
{
    FUNC_NAME
    qDebug() << "At index: " << idx;
    if (idx < 0) idx = 0;
    else if (idx > rowCount()) idx = rowCount();
    else {
        // do nothing
    }

    MyItem *newItem = new MyItem(_data, _color, _textColor);
    beginInsertRows(QModelIndex(), idx, idx);       // add 1 item to idx => begin = idx & end = idx
    m_listItems.insert(idx, newItem);
    endInsertRows();

}

void MyListModel::changeItemAt(int idx, QString _data, QString _color, QString _textColor)
{
    if (idx < 0 || idx >= rowCount())
        return;
    MyItem *item = m_listItems.at(idx);
    item->setData(_data);
    item->setColor(_color);
    item->setTextColor(_textColor);

    emit dataChanged(index(idx), index(idx));   // must emit this signal to update in qml
}

void MyListModel::deleteItem(int idx)
{
    FUNC_NAME
    if (idx < 0 || idx > rowCount() || rowCount() == 0)
    {
        qDebug() << "Delete an invalid item at: " << idx;
        return;
    }
    MyItem *delItem = m_listItems[idx];
    beginRemoveRows(QModelIndex(), idx, idx);
    m_listItems.removeAt(idx);
    endRemoveRows();

    if (delItem != nullptr)
    {
        delete delItem;
        delItem = nullptr;
    }
}

QHash<int, QByteArray> MyListModel::roleNames() const
{
    QHash<int, QByteArray> table;
    table[Data] = "Data";
    table[Color] = "Color";
    table[TextColor] = "TextColor";
    return table;
}
