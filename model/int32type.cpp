#include "int32type.h"
#include "exception/qtexception.h"

Int32Type::Int32Type(QObject *parent) : Type(parent,"i32",true)
{

}

Type *Int32Type::getPlusOperatorType(Type *other)
{
    if(other == Type::int32Type)
    {
        return this;
    }
    throwExceptionWithLine("not supported");
}
