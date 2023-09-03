#pragma once
class Var;
class InstructionBlock;
class Expression;
#include "instruction.h"

class AssignInstruction : public Instruction
{
    QString varName;
    Expression * initExpr;
public:
    AssignInstruction(QObject * parent,InstructionBlock * parentBlock, const QString & varName, Expression * initExpr);
    virtual void execute()override;
};

