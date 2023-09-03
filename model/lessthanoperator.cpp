#include "lessthanoperator.h"

LessThanOperator::LessThanOperator(QObject *parent,     Expression*  left,Expression*  right)
    : Expression(parent),left(left),right(right)
{

}




bool LessThanOperator::toBool()
{
    return left->evaluate()->lessThan(right->evaluate());
}
