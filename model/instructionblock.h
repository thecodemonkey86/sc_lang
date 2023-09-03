#pragma once

#include <QList>
#include <QHash>
#include "instruction.h"
class Type;
class Var;

class InstructionBlock : public Instruction
{
protected:
    InstructionBlock* parentBlock;
    QList<Instruction*> instructions;
    QHash<QString,Var*> declaredVars;
public:
    InstructionBlock(QObject* parent, InstructionBlock* parentBlock);

    void addInstruction(Instruction* instr) ;
    void declareVariable(Var* var);
    Var * getDeclaredVariable(const QString & name) const;
    void execute();
};

