#pragma once
class Var;
class Expression;
#include "instruction.h"

class DeclareInstruction : public Instruction
{
    Var * var;
    Expression * initExpr;
public:
    DeclareInstruction(QObject * parent, InstructionBlock *parentBlock,Var * var, Expression * initExpr);
    virtual void execute()override;
    Var *getVar() const;
};

