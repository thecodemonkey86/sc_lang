#pragma once

#include "expression.h"

class LessThanOperator : public Expression
{
    Expression*  left;
    Expression*  right;
public:
    explicit LessThanOperator(QObject *parent,     Expression*  left,Expression*  right);


    // Expression interface
public:
    virtual bool toBool() override;
};

