#include "parser.h"
#include "model/parenthesisexpression.h"
#include "model/token.h"
#include "model/tokenlist.h"
#include "qglobal.h"
#include <QString>
#include <algorithm>
#include <exception/qtexception.h>
#include <model/StringConstant.h>



void Parser::addToken(const QString &s, TokenList &tokens, qsizetype &start, qsizetype &i)
{
    QString t=s.mid(start, i-start).trimmed();
    if(!t.isEmpty())
    {
        if(t=="and")
        {
            tokens.append(Token(t,Token::And));
        } else if(t == "or")
        {
            tokens.append(Token(t,Token::Or));
//        } else if(t == "xor")
//        {
//            tokens.append(Token(t,Token::XOr, nullptr));
        } else  if(TokenList::regexDecimalIntExpression.match(t).hasMatch())
        {
            tokens.append(Token(t,Token::IntLiteral));
        } else if(t == "debug")
        {
            tokens.append(Token(t,Token::DebugFunction));
        }  else if(t == "i32")
        {
            tokens.append(Token(t,Token::Int32Type));
        } else
        {
            tokens.append(Token(t,Token::Identifier));
        }



    }


    start=i;
}

void Parser::addToken(const QString &s,TokenList &tokens, qsizetype &start, qsizetype &i, Token::TokenType type, qsizetype offset)
{
     QString t=s.mid(i,offset+1).trimmed();
    addToken(s,tokens,start,i);


    tokens.append(Token(t, type));
    i+=offset;
    start=i+1;
}

void Parser::parseRoot(TokenList &tokens)
{
    for(qsizetype i = 0;i < tokens.size(); ++i)
    {
        switch (tokens[i].getType()) {
        case Token::OpeningParenthesis:

            parseFunction(tokens,i);
            break;
        default:
            break;
        }
    }
}

void Parser::expectNotAtStart(qsizetype start)
{
    if(start<1)
    {
        throwExceptionWithLine("syntax error");
    }
}

QString Parser::getTokenAndExpectTokenType(TokenList &tokens, qsizetype i, Token::TokenType expected)
{
    if(i<0 || i >= tokens.size())
    {
        throwExceptionWithLine("syntax error");
    }
    if(tokens[i].getType() != expected)
    {
        throwExceptionWithLine(QStringLiteral("expected a %1 token at position %2, but got %3").arg(expected).arg(i).arg(tokens[i].getType() ));
    }
    return tokens[i].getToken();
}

QString Parser::getTokenAndExpectTokenType(TokenList &tokens, qsizetype i, QList<Token::TokenType> anyExpected)
{
    if(i<0 || i >= tokens.size())
    {
        throwExceptionWithLine("syntax error");
    }
    if(!anyExpected.contains(tokens[i].getType()))
    {
        QStringList exp;
        for(Token::TokenType e:anyExpected)
        {
            exp += QString::number(e);
        }
        throwExceptionWithLine(QStringLiteral("expected a %1 token at position %2, but got %3").arg(exp.join(" or ")).arg(i).arg(tokens[i].getType() ));
    }
    return tokens[i].getToken();
}

QList<Token::TokenType> Parser::getTypeTokens()
{
    return QList<Token::TokenType>() << Token::Identifier << Token::Int32Type << Token::StringType;
}

void Parser::parseFunction(TokenList &tokens, qsizetype start)
{
    expectNotAtStart(start);
    qsizetype i=start-1;
    QString name = getTokenAndExpectTokenType(tokens,i,Token::Identifier);
    expectNotAtStart(--i);

    switch (tokens[i].getType()) {
    case value:

        break;
    default:
        break;
    }

    QString typeName = getTokenAndExpectTokenType(tokens,--i,getTypeTokens());

    qDebug()<<name;
    qDebug()<<typeName;
}

Expression * Parser::getPlainExpression(TokenList &tokens, qsizetype start, qsizetype end)
{
    for(qsizetype i=start;i<std::min(end,tokens.size()-1);++i)
    {
        switch (tokens[i].getType()) {
        case Token::Multiply:
        {
            //tokens[i].setExpr(new MultiplyExpression(tokens[i-1].getExpr(),tokens[i+1].getExpr()));
            tokens.removeAt(--i);
            tokens.removeAt(i+1);
            break;
        }
//        case Token::Divide:
//        {
//            tokens[i].setExpr(new WorkflowConditionDivideExpression(tokens[i-1].getExpr(),tokens[i+1].getExpr()));
//            tokens.removeAt(--i);
//            tokens.removeAt(i+1);
//            break;
//        }
        default:
            break;
        }
    }
    for(qsizetype i=start;i<std::min(end,tokens.size()-1);++i)
    {
        switch (tokens[i].getType()) {
        case Token::Plus:
        {
            //tokens[i].setExpr(new WorkflowConditionPlusExpression(tokens[i-1].getExpr(),tokens[i+1].getExpr()));
            tokens.removeAt(--i);
            tokens.removeAt(i+1);
            break;
        }
        case Token::Minus:
        {
            //tokens[i].setExpr(new WorkflowConditionMinusExpression(tokens[i-1].getExpr(),tokens[i+1].getExpr()));
            tokens.removeAt(--i);
            tokens.removeAt(i+1);
            break;
        }
        default:
            break;
        }
    }
    if(tokens.size()<start)
    {
        throwExceptionWithLine("syntax error");
    }
    return tokens[start].getExpr();
}


//Expression *Parser::buildAST(TokenList &tokens)
//{
// /*for(int i=offset;i<tokens.size();++i)
// {

//        if(tokens[i].getType()== Token::OpeningParenthesis)
//        {
//            tokens.removeAt(i);
//            ParenthesisExpression * parenthesisExpr=new ParenthesisExpression();
//            auto subExpr= buildAST(tokens,parenthesisExpr,i);
//            parenthesisExpr->setExpr(subExpr);
//            return parenthesisExpr;
//        } else if(tokens[i].getType()== Token::ClosingParenthesis)
//        {
//            tokens.removeAt(i);
//            return parenthesisExpr;
//        }



// }


// if(tokens.size()!=1)
// {
//     throwExceptionWithLine("syntax error");
// }
// return tokens.first().getExpr();*/


//    for(auto & t : tokens)
//    {
//        switch (t.getType()) {

//        case Token::StringLiteral:
//        {
//            t.setExpr(new StringConstant(t.getToken()));
//            break;
//        }
//        case Token::Identifier:
//        {
//           // t.setExpr(new WorkflowConditionVarExpression(t.getToken()));
//            break;
//        }
//        case Token::IntLiteral:
//        {
//           // t.setExpr(new WorkflowConditionIntConstant(t.getToken().toInt()));
//            break;
//        }
//        case Token::FloatLiteral:
//            throwExceptionWithLine("not implemented");
//        default:
//            break;
//        }

//    }

//    bool containsParenthesis=false;
//    do
//    {
//        containsParenthesis = false;
//        for(qsizetype i=tokens.size()-1;i>=0;--i)
//        {
//            if(tokens[i].getType()== Token::OpeningParenthesis)
//            {
//                containsParenthesis = true;
//                ParenthesisExpression * parenthesisExpr = new ParenthesisExpression();
//                for(qsizetype j=i+1;j<tokens.size();++j)
//                {
//                    if(tokens[j].getType()== Token::ClosingParenthesis)
//                    {
//                        tokens.removeAt(j);
//                        parenthesisExpr->setExpr(getPlainExpression(tokens,i+1,j-1));
//                        tokens[i].setExpr(parenthesisExpr);
//                        tokens[i].setType(Token::ParenthesisExpression);
//                        tokens.removeAt(i+1);
//                        break;
//                    }
//                }
//            }
//        }
//    }while(containsParenthesis);


//    return getPlainExpression(tokens,0,tokens.size());
//}



Expression *Parser::parse(const QString &s)
{
   // WorkflowExpression * expr=nullptr;
    bool quot=false;
    bool escape=false;
    TokenList tokens;
    qsizetype start=0;
    for(qsizetype i=0;i<s.size();++i)
    {
        if(!quot)
        {
            switch (s[i].toLatin1()) {
                case '"':
                {
                     quot =true;
                     addToken(s,tokens,start,i);
                     break;
                }
                case ' ':
                case '\r':
                case '\n':
                case '\t':
                {
                     addToken(s,tokens,start,i);
                     break;
                }
                case '+':
                {
                     addToken(s,tokens,start,i,Token::Plus);
                     break;
                }
                case '-':
                {
                     addToken(s,tokens,start,i,Token::Minus);
                     break;
                }
                case '*':
                {
                     addToken(s,tokens,start,i,Token::Multiply);
                     break;
                }
                case '/':
                {
                     addToken(s,tokens,start,i,Token::Divide);
                     break;
                }
                case '(':
                {
                     addToken(s,tokens,start,i,Token::OpeningParenthesis);
                     break;
                }
                case ')':
                {
                     addToken(s,tokens,start,i,Token::ClosingParenthesis);
                     break;
                }
                case '{':
                {
                     addToken(s,tokens,start,i,Token::OpeningBrace);
                     break;
                }
                case '}':
                {
                     addToken(s,tokens,start,i,Token::ClosingBrace);
                     break;
                }
                case '[':
                {
                     if(i<s.size() +1)
                     {
                        switch (s[i+1].toLatin1()) {
                        case ']':
                        {
                            addToken(s,tokens,start,i,Token::ArrayType,1);
                            break;
                        }
                        default:
                        {
                            addToken(s,tokens,start,i,Token::OpeningBracket);
                        }
                        }
                     }
                     break;
                }
                case ']':
                {
                     addToken(s,tokens,start,i,Token::ClosingBracket);
                     break;
                }
                case '>':
                {
                     if(i<s.size() +1)
                     {
                         switch (s[i+1].toLatin1()) {
                         case '=':
                         {
                             addToken(s,tokens,start,i,Token::GreaterThanOrEqual,1);
                             break;
                         }
                         default:
                         {
                             addToken(s,tokens,start,i,Token::GreaterThan);
                         }
                         }
                     }
                     break;
                }
                case '<':
                {
                     if(i<s.size() +1)
                     {
                         switch (s[i+1].toLatin1()) {
                         case '=':
                         {
                             addToken(s,tokens,start,i,Token::LessThanOrEqual,1);
                             break;
                         }
                         case '<':
                         {
                             addToken(s,tokens,start,i,Token::ShiftOperator,1);
                             break;
                         }
                         default:
                         {
                             addToken(s,tokens,start,i,Token::LessThan);
                         }
                         }
                     }
                     break;
                }
                case '!':
                {
                     if(i<s.size() +1)
                     {
                         switch (s[i+1].toLatin1()) {
                         case '=':
                         {
                             addToken(s,tokens,start,i,Token::NotEquals,1);
                             break;
                         }
                         default:
                         {
                             addToken(s,tokens,start,i,Token::Not);
                         }
                         }
                     }
                     break;
                }
                case '=':
                {
                     if(i<s.size() +1)
                     {
                         switch (s[i+1].toLatin1()) {
                         case '=':
                         {
                             addToken(s,tokens,start,i,Token::Equals,1);
                             break;
                         }
                         default:
                         {
                             addToken(s,tokens,start,i,Token::Assign);
                         }
                         }
                     }
                     break;
                }
                case ';':
                {
                     addToken(s,tokens,start,i,Token::Semicolon);
                     break;
                }
                default:
                     break;

            }
        } else {
            switch (s[i].toLatin1()) {
                case '\\':
                {
                     escape =true;
                     break;
                }
                case '"':
                {
                     if(!escape) {
                         quot =false;
                         QString str=s.mid(start+1, i-start-1);
                         tokens.append(Token(str, Token::StringLiteral));
                     }
                    break;
                }

                default:
                    break;
            }
        }
    }
    auto i=s.length();
 addToken(s,tokens,start,i);
#ifdef QT_DEBUG
    for(const Token &t:tokens)
    {
        qDebug().noquote()<<t.getToken()<<":  "<<t.getType();
        qDebug()<<"---------------";
    }
#endif

    parseRoot(tokens);
    //return buildAST(tokens);
    return nullptr;
}

