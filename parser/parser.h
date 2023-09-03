#pragma once

#include <QRegularExpression>
#include <memory>
using std::shared_ptr;
#include "model/token.h"

class InstructionBlock;
class Function;
class AST;
class WorkflowConditionParenthesisExpression;


class TokenList;
class QString;
class Expression;

class Parser : public QObject
{
    Q_OBJECT
public:
    Parser()=default;
    
       AST*   parse(const QString & s);

private:
     char getChar(const QString &s, qsizetype i);
   void addToken(const QString &s, TokenList &tokens, qsizetype &start, qsizetype &currentPos);
   void addToken(const QString &s, TokenList &tokens, qsizetype &start, qsizetype &currentPos, Token::TokenType type, qsizetype offset=0);
//   Expression * buildAST(TokenList &tokens);

   void parseRoot(AST *ast, TokenList &tokens);
   Expression*  getExpression(TokenList &tokens, qsizetype pos,InstructionBlock *instrBlock);
   Expression*   getPlainExpression(TokenList &tokens, qsizetype pos,InstructionBlock *instrBlock);
   Function *parseMainFunction(TokenList &tokens, qsizetype i);
   void parseInstructions(InstructionBlock *instrBlock, TokenList &tokens, qsizetype &currentPos);
   void expectValidPosition(TokenList &tokens,qsizetype i);
   QString getTokenAndExpectTokenType(TokenList &tokens,qsizetype i, Token::TokenType expected);
   void expectToken(TokenList &tokens, qsizetype i, const char *expected);
   void expectTokenType(TokenList &tokens, qsizetype i, Token::TokenType expected);
   QString getTokenAndExpectTokenType(TokenList &tokens, qsizetype i, QList<Token::TokenType> anyExpected);
   bool checkTokenType(TokenList &tokens, qsizetype i, QList<Token::TokenType> anyExpected);

   QList<Token::TokenType> getTypeTokens();
   qsizetype getExpressionEndPos(TokenList &, qsizetype pos);
};

