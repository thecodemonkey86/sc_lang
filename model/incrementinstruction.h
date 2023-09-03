#pragma once

#include "instruction.h"

class Expression;
class IncrementInstruction : public Instruction
{
    Expression * expr;
public:
    explicit IncrementInstruction(QObject *parent, InstructionBlock *instrBlock, Expression * expr);

    // Instruction interface
public:
    virtual void execute() override;
};

