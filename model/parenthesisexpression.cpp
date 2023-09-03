#include "parenthesisexpression.h"

ParenthesisExpression::ParenthesisExpression(QObject *parent, Expression *expr)
    :Expression(parent),expr(expr)
{

}

Expression *ParenthesisExpression::evaluate()
{
    return expr->evaluate();
}

int ParenthesisExpression::toInt()
{
    return expr->toInt();
}

Expression *ParenthesisExpression::plus(Expression *other)
{
    return expr->plus(other);
}

Expression *ParenthesisExpression::multiply(Expression *other)
{
    return expr->multiply(other);
}


Type *ParenthesisExpression::getType() const
{
    return expr->getType();
}
