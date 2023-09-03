#pragma once
class Function;
#include <QObject>

class AST : public QObject
{
    Q_OBJECT
    Function * mainFn;
public:
    AST(QObject * parent);

    void setMainFn(Function * mainFn);

    void run();
};

