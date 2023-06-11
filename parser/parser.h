#pragma once

#include <QRegularExpression>

#include "model/token.h"

class WorkflowConditionParenthesisExpression;


class TokenList;
class QString;
class Expression;

class Parser
{
public:
    Parser()=delete;
    
    static  Expression * parse(const QString & s);
private:
  static void addToken(const QString &s, TokenList &tokens, qsizetype &start, qsizetype &i);
  static void addToken(const QString &s, TokenList &tokens, qsizetype &start, qsizetype &i, Token::TokenType type, qsizetype offset=0);
//  static Expression * buildAST(TokenList &tokens);

  static void parseRoot(TokenList &tokens);
  static Expression *getPlainExpression(TokenList &tokens, qsizetype start, qsizetype end);
  static void parseFunction(TokenList &tokens, qsizetype start);
  static void expectNotAtStart(qsizetype start);
  static QString getTokenAndExpectTokenType(TokenList &tokens,qsizetype i, Token::TokenType expected);
  static QString getTokenAndExpectTokenType(TokenList &tokens, qsizetype i, QList<Token::TokenType> anyExpected);

  static QList<Token::TokenType> getTypeTokens();
};

