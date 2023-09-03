#include "plusoperator.h"
#include "type.h"

QString PlusOperator::toString() const
{
    return QStringLiteral("%1 + %2").arg(left->toString(),right->toString());
}

Expression *PlusOperator::evaluate()
{
    return left->evaluate()->plus(right->evaluate());
}

Type *PlusOperator::getType() const
{
    return left->getType()->getPlusOperatorType(left->getType());
}

int PlusOperator::toInt()
{
    return evaluate()->toInt();
}

PlusOperator::PlusOperator(QObject *parent, Expression*  left,
                           Expression*  right) : Expression(parent), left(left),
    right(right)
{}


