#pragma once
#include "expression.h"

class AndOperator : public Expression
{
   Expression* left;
   Expression*  right;
public:

    AndOperator( QObject *parent,Expression*  left,
                          Expression*  right);

};

