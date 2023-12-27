#pragma once

#include "expression.h"
#include "instructionblock.h"

class Expression;
class WhileLoop : public InstructionBlock
{
    Expression * cond ;
public:
    explicit WhileLoop(QObject *parent,InstructionBlock* parentBlock, Expression *cond);

    // Instruction interface
public:
    virtual void execute() override;
};

