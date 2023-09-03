#include "assigninstruction.h"
#include "expression.h"
#include "instructionblock.h"
#include <QDebug>



AssignInstruction::AssignInstruction(QObject * parent, InstructionBlock *parentBlock, const QString &varName, Expression *initExpr)
    : Instruction(parent,parentBlock),
    varName(varName),
    initExpr(initExpr)
{

}


void AssignInstruction::execute(){
//    parentBlock->getDeclaredVariable(varName)-
    //qDebug()<<initExpr->toInt();
}
