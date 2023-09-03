#include "unaryminusoperator.h"

#include "exception/qtexception.h"

UnaryMinusOperator::UnaryMinusOperator( QObject * parent,Expression*  expr)
    : Expression(parent), expr(expr) {}


QString UnaryMinusOperator::toString() const
{
    return QStringLiteral("-%1").arg(expr->toString());
}

Type *UnaryMinusOperator::getType() const
{
    return expr->getType();
}

