#pragma once

#include "expression.h"
#include "instructionblock.h"

class Expression;
class ForLoop : public InstructionBlock
{
    Instruction * start;
    Instruction * step;
    Expression * cond ;
public:
    explicit ForLoop(QObject *parent,InstructionBlock* parentBlock, Instruction * start, Expression *cond, Instruction *step);

    // Instruction interface
public:
    virtual void execute() override;
};

