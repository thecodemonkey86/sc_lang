#pragma once

#include "expression.h"
#include "qobject.h"

class IntConstant : public Expression
{
    int val;
public:
    IntConstant(QObject * parent, int val);

    // Expression interface
public:
    virtual QString toString() const override;
    Type *getType() const override;

    virtual int toInt() override;
    virtual Expression *plus(Expression *other) override;
    virtual Expression *multiply(Expression *other) override;
    virtual bool lessThan(Expression *other) override;
    virtual bool greaterThan(Expression *other) override;
    virtual Expression *increment() override;
};

