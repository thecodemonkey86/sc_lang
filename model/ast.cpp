#include "ast.h"
#include "function.h"

AST::AST(QObject * parent) : QObject(parent),mainFn(nullptr)
{

}

void AST::setMainFn(Function * mainFn)
{
    this->mainFn = mainFn;
}

void AST::run()
{
    if(mainFn) {
        mainFn->execute();
    }
}
