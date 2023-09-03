#include "oroperator.h"


OrOperator::OrOperator(QObject *parent, Expression *left, Expression *right)
    :Expression(parent),left(left),right(right)
{

}

QString OrOperator::toString() const
{
    return QStringLiteral("%1 or %2").arg(left->toString(),right->toString());
}
