#include "MyItem.h"
#include <QDebug>

MyItem::MyItem(QString data, QString color, QString textColor)
    : m_data { data }
    , m_color { color }
    , m_textColor { textColor }
{
    qDebug() << "Add item: { data: " << m_data << ", color: " << m_color << ", textColor: " << m_textColor << " }";
}

MyItem::~MyItem()
{
    qDebug() << "Delete item: { data: " << m_data << ", color: " << m_color << ", textColor: " << m_textColor << " }";
}

void MyItem::setData(QString data)
{
    m_data = data;
}

void MyItem::setColor(QString color)
{
    m_color = color;
}

void MyItem::setTextColor(QString textColor)
{
    m_textColor = textColor;
}
