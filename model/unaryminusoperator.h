#pragma once
#include "expression.h"


class UnaryMinusOperator : public Expression
{
    Expression*  expr;
 
public:
    UnaryMinusOperator( QObject * parent,Expression*  expr);


    virtual QString toString() const override;

    // Expression interface
public:
    Type *getType() const;
};



