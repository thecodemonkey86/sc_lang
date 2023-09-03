#pragma once

#include "expression.h"

class InstructionBlock;
class AccessVarExpression : public Expression
{
    QString varName;
    InstructionBlock *parentBlock;
public:
    explicit AccessVarExpression(QObject *parent, InstructionBlock *parentBlock, const QString &varName);

    // Expression interface
public:
    virtual Expression *plus(Expression *other) override;
    virtual Expression *multiply(Expression *other) override;
    virtual int toInt() override;
    virtual Expression *evaluate() override;
    virtual Expression *increment() override;
};

