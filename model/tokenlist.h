#pragma once
#include "token.h"
#include <QList>
#include <QRegularExpression>

class TokenList : public QList<Token>
{

    qsizetype pos;
public:
     static QRegularExpression regexDecimalIntExpression;
    TokenList();

    TokenList & incr();
    TokenList & offset(int offset);
    TokenList & decr();

    bool hasNext() const;
    const Token &nextToken();
    const Token &peekCurrToken()const;
    Token::TokenType peekCurrTokenType()const;
    const Token &peekNextToken()const;
    Token::TokenType peekNextTokenType()const;
    const QString &peekTokenStr()const;
    const Token &peekToken(int offset) const;
    const QString &peekTokenStr(int offset)const;
    bool incrIfNextTokenEquals(Token::TokenType t);
    bool incrIfNextTokenNotEquals(Token::TokenType t);
    qsizetype getPos() const;

};

