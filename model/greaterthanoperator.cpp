#include "greaterthanoperator.h"

GreaterThanOperator::GreaterThanOperator(QObject *parent,     Expression*  left,Expression*  right)
    : Expression(parent),left(left),right(right)
{

}




bool GreaterThanOperator::toBool()
{
    return left->evaluate()->greaterThan(right->evaluate());
}
