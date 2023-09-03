#pragma once

#include "expression.h"

class FloatConstant : public Expression
{
    double val;
public:
    FloatConstant(QObject * parent,double val);

    // Expression interface
public:
    virtual QString toString() const override;
};

