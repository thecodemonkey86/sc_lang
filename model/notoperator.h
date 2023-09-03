#include "expression.h"

#pragma once


class NotOperator : public Expression
{
    Expression*  expr;
 
public:
    NotOperator(QObject * parent, Expression*  expr);
    // Expression interface
public:
    virtual QString toString() const override;
};

