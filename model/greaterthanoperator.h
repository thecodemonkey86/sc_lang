#pragma once

#include "expression.h"

class GreaterThanOperator : public Expression
{
    Expression*  left;
    Expression*  right;
public:
    explicit GreaterThanOperator(QObject *parent,     Expression*  left,Expression*  right);


    // Expression interface
public:
    virtual bool toBool() override;
};

