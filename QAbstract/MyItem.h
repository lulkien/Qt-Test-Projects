#ifndef MYITEM_H
#define MYITEM_H

#include <QString>

class MyItem
{
public:
    MyItem(QString data, QString color, QString textColor);
    virtual ~MyItem();

    void setData(QString data);
    void setColor(QString color);
    void setTextColor(QString textColor);

    QString getData() const { return m_data; }
    QString getColor() const { return m_color; }
    QString getTextColor() const { return m_textColor; }

private:
    QString m_data;
    QString m_color;
    QString m_textColor;
};

#endif // MYITEM_H
