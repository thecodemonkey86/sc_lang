#pragma once


#include "qobject.h"

class InstructionBlock;
class Instruction : public QObject
{
    Q_OBJECT
protected:
    InstructionBlock * parentBlock;
public:
    Instruction(QObject *parent,InstructionBlock * parentBlock);
    virtual void execute()=0;
};

