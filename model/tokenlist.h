#pragma once
#include "token.h"
#include <QList>
#include <QRegularExpression>

class TokenList : public QList<Token>
{

    qsizetype pos;
public:
    static const QRegularExpression INT_EXPRESSION;
    static const QRegularExpression FLOAT_EXPRESSION;
    TokenList();
    TokenList(const QList<Token> & tokens);

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

    void secureRemoveAt(qsizetype i);
    const Token &secureAccess(qsizetype i)const;

    const QString &secureAccessStr(qsizetype i)const;
    Token::TokenType secureAccessType(qsizetype i) const;
};


