#pragma once
#include <QString>

class Expression;

class Token
{
    Expression * expr;
public:
    enum TokenType{StringLiteral,
                     Identifier,
                    Int32Type,
                     StringType,
                   OpeningParenthesis,
                   ClosingParenthesis,
                   OpeningBracket,
                   ClosingBracket,
                     OpeningBrace,
                     ClosingBrace,
                   ArrayType,
                   ParenthesisExpression,
                   Assign,
                   Equals,
                   NotEquals,
                   GreaterThan,
                   GreaterThanOrEqual,
                   LessThan,
                   LessThanOrEqual,
                   Not,
                   Plus,
                   Minus,
                   Multiply,
                   Divide,
                   Or,
                   And,
                   ShiftOperator,
                   Semicolon,
//                   XOr,
                    IntLiteral,
                     FloatLiteral,
                     DebugFunction
                  };
private:
    QString token;
    TokenType type;

public:
    Token(const QString &token,TokenType type);
    Token(TokenType type);
    const QString &getToken()const;
    TokenType getType() const;
    bool isIdentifier()const;
    
    Expression *getExpr() const;
    void setExpr(Expression *newExpr);
    void setType(TokenType newType);
    void setToken(const QString &newToken);
};

