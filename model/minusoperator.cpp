#include "minusoperator.h"


QString MinusOperator::toString() const
{
    return QStringLiteral("%1 - %2").arg(left->toString(),right->toString());
}

MinusOperator::MinusOperator(QObject *parent, Expression*  left,  Expression*  right) : Expression(parent), left(left),
   right(right)
{}
