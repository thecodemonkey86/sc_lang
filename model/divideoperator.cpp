#include "divideoperator.h"



QString DivideOperator::toString() const
{
    return QStringLiteral("%1 / %2").arg(left->toString(),right->toString());
}

DivideOperator::DivideOperator(QObject * parent, Expression*  left,  Expression*  right) : Expression(parent), left(left),
    right(right)
{}
