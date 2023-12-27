#include "instructionblock.h"
#include "var.h"
#include <exception/qtexception.h>


InstructionBlock::InstructionBlock(QObject *parent, InstructionBlock*  parentBlock) : Instruction(parent,parentBlock), parentBlock(parentBlock)
{

}


void InstructionBlock::addInstruction(Instruction* instr)
{
    instructions += instr;
}

void InstructionBlock::declareVariable(Var* var)
{
    if(declaredVars.contains(var->getName()))
    {
        throwExceptionWithLine(QStringLiteral("variable %1 already delared").arg(var->getName()));
    }
    declaredVars.insert(var->getName(),var);
}

Var *InstructionBlock::getDeclaredVariable(const QString &name) const
{
    if(declaredVars.contains(name)) {
        return declaredVars[name];
    } else if(parentBlock!=nullptr) {
        return parentBlock->getDeclaredVariable(name);
    } else {
        throwExceptionWithLine(QStringLiteral("variable %1 is not declared").arg(name));
    }
}

void InstructionBlock::execute()
{
    for(auto i : instructions)
    {
        i->execute();
    }
    declaredVars.clear();
}
