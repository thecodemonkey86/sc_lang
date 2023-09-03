#pragma once

#include "type.h"

class Int32Type : public Type
{
public:
    Int32Type(QObject * parent);

    // Type interface
public:
    Type *getPlusOperatorType(Type *other);
};

