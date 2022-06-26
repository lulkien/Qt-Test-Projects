#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QObject>
#include <QString>
#include <QByteArray>

#define DEF_VAR(_type, _name, _value) \
    Q_PROPERTY(_type _name READ _name CONSTANT) \
    public: _type _name() { return _value; }

class Constant : public QObject
{
    Q_OBJECT
    DEF_VAR(int     ,   WINDOWS_WIDTH       ,   1280)
    DEF_VAR(int     ,   WINDOWS_HEIGHT      ,   720)
private:
    Constant() {}
    virtual ~Constant() {}
public:
    static Constant &instance()
    {
        static Constant constants;
        return constants;
    }
};

#endif //CONSTANTS_H
