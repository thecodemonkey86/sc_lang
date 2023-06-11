#include "token.h"



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


Token::Token(const QString &token, TokenType type) : expr(nullptr), token(token), type(type)
{

}

Token::Token(TokenType type) : type(type)
{

}

const QString & Token::getToken() const
{
    return token;
}


