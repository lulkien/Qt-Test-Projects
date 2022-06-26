#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QQmlEngine>

#define DEF_CONST(_type, _name, _value) \
    Q_PROPERTY(_type _name READ _name CONSTANT) \
    public: _type _name() { return _value; }

class Constant : public QObject
{
    Q_OBJECT
    DEF_CONST(int       ,   WINDOWS_WIDTH       ,   1280            )
    DEF_CONST(int       ,   WINDOWS_HEIGHT      ,   720             )
    DEF_CONST(QString   ,   BG_COLOR            ,   "#2F2F2F"       )
    DEF_CONST(QString   ,   SLIM_WHITE          ,   "#DADADA"       )
    DEF_CONST(QString   ,   INVISIBLE           ,   "transparent"   )
    DEF_CONST(QString   ,   ITEM_FOCUSING       ,   "#66FACB"       )
private:
    Constant()
    {
        QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    }
    virtual ~Constant() {}
public:
    static Constant &instance()
    {
        static Constant constants;
        return constants;
    }
};

#endif //CONSTANTS_H
