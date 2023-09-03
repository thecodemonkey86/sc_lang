#pragma once

#include "expression.h"

class MinusOperator : public Expression
{
     Expression*  left;
     Expression*  right;
public:
    MinusOperator(QObject * parent, Expression*  left,  Expression*  right);

    // Expression interface
public:
    virtual QString toString() const override;
};

