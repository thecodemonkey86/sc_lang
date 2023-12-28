#include "stringconstant.h"

StringConstant::StringConstant(QObject *parent, const QString &str)
    : Expression(parent), str(str)
{

}

StringConstant *StringConstant::evaluate()
{
    return this;
}



void StringConstant::debug()
{
    qDebug().noquote()<<str;
}
