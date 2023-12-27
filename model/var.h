#include "expression.h"

#include <QObject>
#include <QString>

#pragma once



class Type;
class Var : public Expression
{
    Q_OBJECT
protected:
    Type * type;
    QString name;
public:
    Var(QObject * parent, Type * type, const QString & name);

    virtual Expression* increment();
    virtual void setValue(Expression * expr)=0;
    QString getName() const;
    static Var * create(QObject * parent, Type * type, const QString & name);
};

