#pragma once

#include "expression.h"
#include <QString>
class StringConstant : public Expression
{
    QString str;
public:
    StringConstant(QObject * parent,const QString & str);


    // Expression interface
public:
    StringConstant *evaluate() override;

    // Expression interface
public:
    virtual void debug() override;
};

