#include "declareinstruction.h"
#include "expression.h"
#include "model/instructionblock.h"
#include <QDebug>
#include <model/var.h>

Var *DeclareInstruction::getVar() const
{
    return var;
}

DeclareInstruction::DeclareInstruction(QObject * parent, InstructionBlock *parentBlock, Var *var, Expression *initExpr)
    : Instruction(parent,parentBlock),
    var(var),
    initExpr(initExpr)
{

}


void DeclareInstruction::execute(){
    parentBlock->declareVariable(var);
    var->setValue(initExpr->evaluate());
    //qDebug()<<initExpr->toInt();
}
