#include "var.h"

#include <QObject>
#include <QString>

#pragma once


class I32Var : public Var
{
    int32_t val;
public:
    I32Var(QObject * parent, const QString & name ,int32_t initValue);

    // Var interface
public:
    virtual Expression* increment() override;
    virtual void setValue(Expression *expr) override;
    virtual bool lessThan(Expression *other) override;
    virtual void debug() override;
};

