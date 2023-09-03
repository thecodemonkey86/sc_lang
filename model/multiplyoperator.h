#pragma once

#include "expression.h"

class MultiplyOperator : public Expression
{
     Expression*  left;
     Expression*  right;
public:
    MultiplyOperator(QObject * parent, Expression*  left,  Expression*  right);

    // Expression interface
public:
    virtual QString toString() const override;

    virtual Expression *evaluate() override;
    virtual Type *getType() const override;
    virtual int toInt() override;
};

