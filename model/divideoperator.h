#pragma once

#include "expression.h"

class DivideOperator : public Expression
{
     Expression*  left;
     Expression*  right;
public:
    DivideOperator( QObject * parent,Expression*  left,  Expression*  right);

    // Expression interface
public:
    virtual QString toString() const override;
};

