#include "var.h"
#include "qobject.h"

QString Var::getName() const
{
    return name;
}

Expression *Var::getValue() const
{
    return value;
}

void Var::setValue(Expression *newValue)
{
    value = newValue;
}

Var::Var(QObject * parent,Type * type, const QString & name) : QObject(parent),type(type) , name(name)
{

}
