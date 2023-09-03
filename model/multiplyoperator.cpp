#include "multiplyoperator.h"

QString MultiplyOperator::toString() const
{
    return QStringLiteral("%1 * %2").arg(left->toString(),right->toString());
}

Expression *MultiplyOperator::evaluate()
{
    return left->evaluate()->multiply(right->evaluate());
}

Type *MultiplyOperator::getType() const
{
    return left->getType();
}

int MultiplyOperator::toInt()
{
    return evaluate()->toInt();
}

MultiplyOperator::MultiplyOperator(QObject * parent, Expression*  left,  Expression*  right) : Expression(parent), left(left),
    right(right)
{}
