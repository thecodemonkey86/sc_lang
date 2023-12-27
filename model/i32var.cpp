#include "i32var.h"
#include "int32type.h"
#include "exception/qtexception.h"

I32Var::I32Var(QObject *parent, const QString &name, int32_t initValue) : Var(parent, Type::int32Type,name), val(initValue)
{

}


Expression* I32Var::increment()
{
    val++;
    return this;
}


void I32Var::setValue(Expression *expr)
{
    val = expr->evaluate()->toInt();
}


bool I32Var::lessThan(Expression *other)
{
    auto otherExpr=other->evaluate();
    if(other->getType()->isInt32Type()) {
        return val<otherExpr->toInt();
    }
    throwExceptionWithLine("unsupported operation");
}


void I32Var::debug()
{
    qDebug()<<name<<":"<< val;
}
