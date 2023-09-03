#include <QObject>
#include <QString>

class Expression;
#pragma once



class Type;
class Var : public QObject
{
    Q_OBJECT
    Type * type;
    QString name;
    Expression * value;
public:
    Var(QObject * parent, Type * type, const QString & name);


    QString getName() const;
    Expression *getValue() const;
    void setValue(Expression *newValue);
};

