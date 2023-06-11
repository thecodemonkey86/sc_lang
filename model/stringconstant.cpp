#include "stringconstant.h"

StringConstant::StringConstant(const QString &str) : Expression(), str(str)
{

}

StringConstant *StringConstant::evaluate()
{
    return this;
}

