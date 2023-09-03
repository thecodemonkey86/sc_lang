#pragma once
#include "expression.h"

class OrOperator : public Expression
{
    Expression*  left;
     Expression*  right;
public:
    OrOperator(QObject * parent,    Expression*  left,
               Expression*  right);


    // Expression interface
public:
    virtual QString toString() const override;
};

