#include "FloatConstant.h"

FloatConstant::FloatConstant(QObject *parent, double val) : Expression(parent), val(val)
{

}


QString FloatConstant::toString() const
{
    return QString::number(val);
}
