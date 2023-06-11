#pragma once
#include <QObject>
#include <QCoreApplication>
class Expression : public QObject
{
    Q_OBJECT
public:
    Expression();

    virtual Expression * evaluate()=0;
};

