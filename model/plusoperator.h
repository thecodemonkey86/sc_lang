#pragma once

#include "expression.h"

class PlusOperator : public Expression
{
     Expression*  left;
     Expression*  right;
public:
    PlusOperator( QObject * parent,Expression*  left,  Expression*  right);

public:
    virtual QString toString() const override;

    // Expression interface
public:
    virtual Expression *evaluate() override;
    virtual Type *getType() const override;
    virtual int toInt() override;
};

