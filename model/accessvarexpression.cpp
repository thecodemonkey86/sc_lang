#include "accessvarexpression.h"
#include <model/instructionblock.h>
#include <model/var.h>

AccessVarExpression::AccessVarExpression( QObject *parent, InstructionBlock * parentBlock,const QString & varName)
    : Expression(parent),parentBlock(parentBlock),varName(varName)
{

}


Expression *AccessVarExpression::plus(Expression *other)
{
    return evaluate()->plus(other->evaluate());
}

Expression *AccessVarExpression::multiply(Expression *other)
{
    return evaluate()->multiply(other->evaluate());
}

int AccessVarExpression::toInt()
{
    return evaluate()->toInt();
}


Expression *AccessVarExpression::evaluate()
{
    return parentBlock->getDeclaredVariable(varName)->getValue();
}


Expression *AccessVarExpression::increment()
{
    return evaluate()->increment();
}
