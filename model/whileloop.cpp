#include "whileloop.h"
#ifdef QT_DEBUG
#include <model/var.h>
#endif
WhileLoop::WhileLoop(QObject *parent,InstructionBlock* parentBlock, Expression *cond)
    : InstructionBlock(parent,parentBlock),cond(cond)
{

}


void WhileLoop::execute()
{
    while(cond->evaluate()->toBool())
    {
        InstructionBlock::execute();
    }


}
