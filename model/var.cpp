#include "var.h"
#include "qobject.h"
#include "type.h"
#include "i32var.h"
#include "exception/qtexception.h"

QString Var::getName() const
{
    return name;
}

Var *Var::create(QObject *parent, Type *type, const QString &name)
{
    if(type == Type::int32Type) {
        return new I32Var(parent,name,0);
    }

    throwExceptionWithLine("unsupported operation");
}


Var::Var(QObject * parent,Type * type, const QString & name) : Expression(parent),type(type) , name(name)
{

}

Expression *Var::increment()
{
    throwExceptionWithLine("unsupported operation");
}
