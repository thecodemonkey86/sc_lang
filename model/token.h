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
                     Int64Type,
                     Int8Type,
                     Int16Type,
                     UInt32Type,
                     UInt64Type,
                     UInt8Type,
                     UInt16Type,
                     StringType,
                   OpeningParenthesis,
                   ClosingParenthesis,
                   OpeningBracket,
                   ClosingBracket,
                     OpeningBrace,
                     ClosingBrace,
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
                   Increment,
                   Minus,
                    UnaryMinus,
                   Multiply,
                   Divide,
                   Or,
                   And,
                   ShiftOperator,
                   Semicolon,
//                   XOr,
                    IntLiteral,
                     FloatLiteral,
                     DebugFunction,
                     ForLoop,
                     WhileLoop
                  };
private:
    QString token;
    TokenType type;

public:
    Token(const QString &token,TokenType type);
    Token(const QString &token,TokenType type,Expression * expr);
    Token(TokenType type);
    const QString &getToken()const;
    TokenType getType() const;
    bool isIdentifier()const;
    
    Expression *getExpr() const;
    void setExpr(Expression *newExpr);
    void setType(TokenType newType);
    void setToken(const QString &newToken);

    static QString tokenTypeToString(TokenType type);
};

