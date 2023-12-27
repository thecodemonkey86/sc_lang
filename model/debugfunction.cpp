#include "debugfunction.h"
#include <QDebug>
#include "expression.h"

DebugFunction::DebugFunction(QObject *parent, InstructionBlock * parentBlock, Expression * debug)
    : Instruction(parent,parentBlock),debug(debug)
{

}


void DebugFunction::execute()
{
    debug->evaluate()->debug();
}
