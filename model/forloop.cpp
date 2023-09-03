#include "forloop.h"
#ifdef QT_DEBUG
#include <model/var.h>
#endif
ForLoop::ForLoop(QObject *parent,InstructionBlock* parentBlock, Instruction *start, Expression *cond, Instruction *step)
    : InstructionBlock(parent,parentBlock),start(start),cond(cond),step(step)
{

}


void ForLoop::execute()
{
    for(start->execute();cond->evaluate()->toBool();step->execute())
    {
        #ifdef QT_DEBUG
        qDebug()<<parentBlock->getDeclaredVariable("i")->getValue()->toInt();
        #endif
        for(const auto & i : instructions)
        {
            i->execute();
        }
    }


}
