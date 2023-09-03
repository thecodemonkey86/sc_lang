#pragma once
#include "instructionblock.h"
#include "qobject.h"



class Function : public InstructionBlock
{
    QString name;
public:
    Function(QObject * parent, const QString & name);
};

