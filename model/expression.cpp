
#include "expression.h"
#include <exception/qtexception.h>

Expression::Expression(QObject *parent) : QObject(parent)
{

}

Expression *Expression::evaluate()
{
    return this;
}

Type *Expression::getType() const
{
    throwExceptionWithLine("subclasses must reimplement");
}


void Expression::debug()
{

}

void Expression::assign(Expression *other)
{
    throwExceptionWithLine("runtime exception: unsupported operation: assign");
}

QString Expression::toString()const {
    throwExceptionWithLine("runtime exception: subclasses must override toString");
}

Expression *Expression::plus(Expression *other)
{
    throwExceptionWithLine("runtime exception: unsupported operator: +");
}

bool Expression::lessThan(Expression *other)
{
    throwExceptionWithLine("runtime exception: unsupported operation: <");
}

bool Expression::greaterThan(Expression *other)
{
    throwExceptionWithLine("runtime exception: unsupported operation: >");
}

Expression *Expression::increment()
{
    throwExceptionWithLine("runtime exception: unsupported operator: ++");
}
Expression *Expression::multiply(Expression *other)
{
    throwExceptionWithLine("runtime exception: unsupported operator: *");
}
int Expression::toInt()
{
    throwExceptionWithLine("runtime exception: can not be evaluated as int");
}

bool Expression::toBool()
{
    throwExceptionWithLine("runtime exception: can not be evaluated as bool");
}
