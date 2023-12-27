#include "type.h"
#include "exception/qtexception.h"
#include "int32type.h"
#include <QCoreApplication>
bool Type::getPrimitive() const
{
    return primitive;
}

Type *Type::typeForName(const QString &name)
{
    return declaredTypes.contains(name) ? declaredTypes[name] : getTypePlaceholder(name);
}

bool Type::getIsPlaceholder() const
{
    return isPlaceholder;
}

void Type::setIsPlaceholder(bool newIsPlaceholder)
{
    isPlaceholder = newIsPlaceholder;
}

QString Type::getName() const
{
    return name;
}

void Type::initPrimitiveTypes()
{
    declaredTypes.insert(int32Type->getName(),int32Type);
}

Type *Type::getPlusOperatorType(Type *other)
{
    throwExceptionWithLine("plus operator is unsupported");
}

bool Type::isInt32Type() const
{
    return this== Type::int32Type;
}

Type *Type::getTypePlaceholder(const QString &name)
{
    if(!typePlaceholders.contains(name))
    {
        auto t=new Type(qApp,name);
        t->setIsPlaceholder(true);
        typePlaceholders.insert(name,t);
        return t;
    }
    return typePlaceholders[name];
}

Type::Type(QObject * parent, const QString &name, bool primitive) : QObject(parent) ,name(name), primitive(primitive),isPlaceholder(false)
{

}

Type::Type(QObject * parent, const QString &name) : QObject(parent), name(name), primitive(false),isPlaceholder(false)
{

}

Type* Type::int32Type = new Int32Type(qApp);
QHash<QString,Type*> Type::declaredTypes;
QHash<QString,Type*> Type::typePlaceholders;
