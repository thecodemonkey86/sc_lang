#include "intconstant.h"
#include "exception/qtexception.h"
#include "type.h"
#include "int32type.h"

IntConstant::IntConstant(QObject *parent, int val) : Expression(parent), val(val)
{

}



QString IntConstant::toString() const
{
    return QString::number(val);
}

Type *IntConstant::getType() const
{
    return Type::int32Type;
}

int IntConstant::toInt()
{
    return val;
}

Expression *IntConstant::plus(Expression *other)
{
    if(other->getType() == Type::int32Type) {
        return new IntConstant(qApp,toInt()+other->toInt());
    }
    throwExceptionWithLine("unsupported op");
}

Expression *IntConstant::multiply(Expression *other)
{
    if(other->getType() == Type::int32Type) {
        return new IntConstant(qApp,toInt()*other->toInt());
    }
    throwExceptionWithLine("unsupported op");
}


bool IntConstant::lessThan(Expression *other)
{
    if(other->getType() == Type::int32Type) {
       return val < other->toInt();
    }
    throwExceptionWithLine("unsupported op");
}

bool IntConstant::greaterThan(Expression *other)
{
    if(other->getType() == Type::int32Type) {
       return val > other->toInt();
    }
    throwExceptionWithLine("unsupported op");
}

Expression *IntConstant::increment()
{
    return new IntConstant(parent(), val+1);
}


void IntConstant::debug()
{
    qDebug().noquote()<<val;
}
