#pragma once


#include "model/expression.h"
class ParenthesisExpression : public Expression
{
    Expression * expr;
public:
    ParenthesisExpression(QObject * parent,Expression * expr);



    // Expression interface
public:
    virtual Expression *evaluate() override;

    // Expression interface
public:
    virtual int toInt() override;

    // Expression interface
public:
    virtual Expression *plus(Expression *other) override;
    virtual Expression *multiply(Expression *other) override;
    virtual Type *getType() const override;
};



