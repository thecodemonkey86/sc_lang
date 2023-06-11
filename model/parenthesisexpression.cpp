#include "parenthesisexpression.h"


void ParenthesisExpression::setExpr(Expression *newExpr)
{
    expr = newExpr;
}

ParenthesisExpression::ParenthesisExpression() : Expression(), expr(nullptr)
{

}

Expression *ParenthesisExpression::evaluate()
{
    return expr->evaluate();
}
