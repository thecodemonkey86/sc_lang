#include "andoperator.h"



AndOperator::AndOperator(QObject *parent, Expression*  left,  Expression*  right)
    : Expression(parent), left(left), right(right) {}

