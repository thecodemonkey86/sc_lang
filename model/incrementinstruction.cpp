#include "incrementinstruction.h"
#include "expression.h"

IncrementInstruction::IncrementInstruction(QObject *parent, InstructionBlock * instrBlock, Expression *expr)
    : Instruction(parent,instrBlock),expr(expr)
{

}


void IncrementInstruction::execute()
{
    expr->evaluate()->increment();
}
