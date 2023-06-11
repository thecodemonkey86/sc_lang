#pragma once


#include "model/expression.h"
class ParenthesisExpression : public Expression
{
    Expression * expr;
public:
    ParenthesisExpression();



    // Expression interface
public:
    virtual Expression *evaluate() override;
    void setExpr(Expression *newExpr);
};



