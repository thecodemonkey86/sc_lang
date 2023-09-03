#include "NotOperator.h"




NotOperator::NotOperator(QObject * parent, Expression*  expr)
    : Expression(parent), expr(expr) {}


QString NotOperator::toString() const
{
    return QStringLiteral("!%1").arg(expr->toString());
}
