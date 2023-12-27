#pragma once
#include "qobject.h"
#include "qtmetamacros.h"
#include <QCoreApplication>

class Type;
class Expression : public QObject
{
    Q_OBJECT
public:
    Expression(QObject*parent);

    virtual Expression * evaluate();
    virtual Type * getType() const;
    virtual void debug();
    virtual void assign(Expression * other);
    virtual QString toString() const;
    virtual Expression* plus (Expression * other);
    virtual bool lessThan(Expression * other);
    virtual bool greaterThan(Expression * other);
    virtual Expression*increment();
    virtual Expression* multiply (Expression * other);
    virtual int toInt();
    virtual bool toBool();

};

