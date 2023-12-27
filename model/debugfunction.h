#pragma once

#include "instruction.h"

class Expression;
class DebugFunction : public Instruction
{
    Expression * debug;
public:
    explicit DebugFunction(QObject *parent, InstructionBlock * parentBlock, Expression * debug);

    // Instruction interface
public:
    virtual void execute() override;
};

