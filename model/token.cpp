#include "token.h"
#include <exception/qtexception.h>


Token::TokenType Token::getType() const
{
    return type;
}

bool Token::isIdentifier() const
{
return type == Identifier;
}

Expression *Token::getExpr() const
{
return expr;
}

void Token::setExpr(Expression *newExpr)
{
expr = newExpr;
}

void Token::setType(TokenType newType)
{
type = newType;
}

void Token::setToken(const QString &newToken)
{
token = newToken;
}

QString Token::tokenTypeToString(TokenType type)
{
switch (type) {
case Token::StringLiteral:
    return "StringLiteral";
case Token::Identifier:
    return "Identifier";
case Token::Int32Type:
    return "int32";
case Token::StringType:
    return "String type";
case Token::OpeningParenthesis:
    return "(";
case Token::ClosingParenthesis:
    return ")";
case Token::OpeningBracket:
    return "[";
case Token::ClosingBracket:
    return "]";
case Token::OpeningBrace:
    return "{";
case Token::ClosingBrace:
    return "}";
case Token::ParenthesisExpression:
    return "Parenthesis expression";
case Token::Assign:
    return "=";
case Token::Equals:
    return "==";
case Token::NotEquals:
    return "!=";
case Token::GreaterThan:
    return ">";
case Token::GreaterThanOrEqual:
    return ">=";
case Token::LessThan:
    return "<";
case Token::LessThanOrEqual:
    return "<=";
case Token::Not:
    return "!";
case Token::Plus:
    return "+";
case Token::Minus:
    return "-";
case Token::Multiply:
    return "*";
case Token::Divide:
    return "/";
case Token::Or:
    return "||";
case Token::And:
    return "&&";
case Token::ShiftOperator:
    return "<<";
case Token::Semicolon:
    return ";";
case Token::IntLiteral:
    return "int literal";
case Token::FloatLiteral:
    return "float literal";
case Token::DebugFunction:
    return "debug";
case Token::ForLoop:
    return "for";
}
throwExceptionWithLine("not impl: tokenTypeToString for " + QString::number(static_cast<int>(type)));
}


Token::Token(const QString &token, TokenType type) : expr(nullptr), token(token), type(type)
{

}
Token::Token(const QString &token, TokenType type, Expression *expr) : expr(expr), token(token), type(type)
{

}
Token::Token(TokenType type) : type(type)
{

}

const QString & Token::getToken() const
{
    return token;
}


