#include "parser.h"
#include "model/accessvarexpression.h"
#include "model/parenthesisexpression.h"
#include "model/token.h"
#include "model/tokenlist.h"
#include "qcoreapplication.h"
#include "qglobal.h"
#include <QString>
#include <algorithm>
#include <exception/qtexception.h>
#include <model/StringConstant.h>
#include <model/function.h>
#include <model/type.h>
#include <model/var.h>
#include <model/declareinstruction.h>
#include <model/ast.h>
#include <model/unaryminusoperator.h>
#include <model/multiplyoperator.h>
#include <model/divideoperator.h>
#include <model/intconstant.h>
#include <model/plusoperator.h>
#include <model/minusoperator.h>
#include <model/AssignInstruction.h>
#include <model/forloop.h>
#include <model/incrementinstruction.h>
#include <model/greaterthanoperator.h>
#include <model/lessthanoperator.h>
#include <model/whileloop.h>
#include <model/debugfunction.h>

using std::make_shared;

void Parser::addToken(const QString &s, TokenList &tokens, qsizetype &start, qsizetype &currentPos)
{
    QString t=s.mid(start, currentPos-start).trimmed();
    if(!t.isEmpty())
    {
        if(t == "debug")
        {
            tokens.append(Token(t,Token::DebugFunction));
        }  else if(t == "i32")
        {
            tokens.append(Token(t,Token::Int32Type));
        } else if(t == "i64")
        {
            tokens.append(Token(t,Token::Int64Type));
        } else if(t == "i8")
        {
            tokens.append(Token(t,Token::Int8Type));
        } else if(t == "i16")
        {
            tokens.append(Token(t,Token::Int16Type));
        } else if(t == "u32")
        {
            tokens.append(Token(t,Token::UInt32Type));
        } else if(t == "u64")
        {
            tokens.append(Token(t,Token::UInt64Type));
        } else if(t == "u8")
        {
            tokens.append(Token(t,Token::UInt8Type));
        } else if(t == "u16")
        {
            tokens.append(Token(t,Token::UInt16Type));
        } else if(t == "string")
        {
            tokens.append(Token(t,Token::StringType));
        } else if(t == "for")
        {
            tokens.append(Token(t,Token::ForLoop));
        } else if(t == "while")
        {
            tokens.append(Token(t,Token::WhileLoop));
        } else if(!t.isEmpty()){
            if(TokenList::INT_EXPRESSION.match(t).hasMatch())
            {
                tokens.append(Token(t,Token::IntLiteral,new IntConstant(qApp, t.toInt())));
            } else if(TokenList::FLOAT_EXPRESSION.match(t).hasMatch())
            {
                tokens.append(Token(t,Token::FloatLiteral));
            } else
            {
                tokens.append(Token(t,Token::Identifier));
            }



        }



    }


    start=currentPos;
}

void Parser::addToken(const QString &s, TokenList &tokens, qsizetype &start, qsizetype &currentPos, Token::TokenType type, qsizetype offset)
{
     QString t=s.mid(currentPos,offset+1).trimmed();
    addToken(s,tokens,start,currentPos);


    tokens.append(Token(t, type));
    currentPos+=offset;
    start=currentPos+1;
}

void Parser::parseRoot(AST * ast,TokenList &tokens)
{
    for(qsizetype i = 0;i < tokens.size(); ++i)
    {
        switch (tokens[i].getType()) {
        case Token::OpeningParenthesis:

            ast->setMainFn(parseMainFunction(tokens,i-1));
            return;
        default:
            break;
        }
    }
}

Expression *Parser::getExpression(TokenList &tokens, qsizetype pos, InstructionBlock *instrBlock)
{
    bool containsParenthesis=false;
    do
    {
        auto endPos=getExpressionEndPos(tokens,pos)-1;
        containsParenthesis = false;
        for(qsizetype i=endPos;i>=pos;--i)
        {
            if(tokens[i].getType()== Token::OpeningParenthesis && (i==0||!tokens[i-1].isIdentifier()))
            {
                for(qsizetype j=i+1;j<=endPos;++j)
                {
                    if(tokens[j].getType()== Token::ClosingParenthesis)
                    {
                        auto expr=getPlainExpression(tokens,i+1,instrBlock);
                        tokens.secureRemoveAt(i);
                        tokens[i].setExpr(new ParenthesisExpression(qApp,expr));
                        tokens[i].setType(Token::ParenthesisExpression);
                        tokens.secureRemoveAt(i+1);
                        break;
                    }
                }
            }
        }
    }while(containsParenthesis);
 //   expectTokenType(tokens,pos+1,expectedAfter);
    return getPlainExpression(tokens,pos,instrBlock);
}

void Parser::expectValidPosition(TokenList &tokens, qsizetype i)
{
    if(i<0 || i >= tokens.size())
    {
        throwExceptionWithLine("syntax error");
    }
}

QString Parser::getTokenAndExpectTokenType(TokenList &tokens, qsizetype i, Token::TokenType expected)
{

    if(tokens[i].getType() != expected)
    {
        throwExceptionWithLine(QStringLiteral("expected a %1 token at position %2, but got %3").arg(Token::tokenTypeToString(expected)).arg(i).arg(Token::tokenTypeToString(tokens[i].getType() )));
    }
    return tokens[i].getToken();
}

void Parser::expectTokenType(TokenList &tokens, qsizetype i, Token::TokenType expected)
{
    expectValidPosition(tokens,i);
    if(tokens[i].getType() != expected)
    {
        throwExceptionWithLine(QStringLiteral("expected a %1 token at position %2, but got %3").arg(Token::tokenTypeToString(expected)).arg(i).arg(Token::tokenTypeToString(tokens[i].getType() )));
    }
}

void Parser::expectToken(TokenList &tokens, qsizetype i, const char * expected)
{
     expectValidPosition(tokens,i);
    if(tokens[i].getToken() != expected)
    {
        throwExceptionWithLine(QStringLiteral("expected a %1 token at position %2, but got %3").arg(expected).arg(i).arg(tokens[i].getType() ));
    }
}

QString Parser::getTokenAndExpectTokenType(TokenList &tokens, qsizetype i, QList<Token::TokenType> anyExpected)
{
   expectValidPosition(tokens,i);
    if(!anyExpected.contains(tokens[i].getType()))
    {
        QStringList exp;
        for(Token::TokenType e:anyExpected)
        {
            exp += Token::tokenTypeToString(e);
        }
        throwExceptionWithLine(QStringLiteral("expected a %1 token at position %2, but got %3").arg(exp.join(" or ")).arg(i).arg(Token::tokenTypeToString(tokens[i].getType() )));
    }
    return tokens[i].getToken();
}

bool Parser::checkTokenType(TokenList &tokens, qsizetype i, QList<Token::TokenType> anyExpected)
{
expectValidPosition(tokens,i);
    for(Token::TokenType e:anyExpected)
    {
        if(e == tokens[i].getType())
        {
            return true;
        }
    }
    return false;
}

QList<Token::TokenType> Parser::getTypeTokens()
{
    return QList<Token::TokenType>() << Token::Identifier << Token::Int32Type << Token::Int64Type<< Token::Int8Type<< Token::Int16Type << Token::UInt32Type << Token::UInt64Type<< Token::UInt8Type<< Token::UInt16Type  << Token::StringType;
}

qsizetype Parser::getExpressionEndPos(TokenList & tokens,qsizetype pos)
{
    qsizetype parenthesisCount=0;
    for(qsizetype i=pos;i<tokens.size();++i)
    {
        if(tokens[i].getType() == Token::Semicolon) {
            return i;
        }  else  if(tokens[i].getType() == Token::OpeningParenthesis) {
            parenthesisCount++;
        } else  if(tokens[i].getType() == Token::ClosingParenthesis) {
            if(parenthesisCount ==0)
            {
                return i;
            }
            parenthesisCount--;
        }
    }
    throwExceptionWithLine("expected semicolon");
}

Function * Parser::parseMainFunction(TokenList &tokens, qsizetype i)
{
    expectToken(tokens,i, "main");
    Function * mainFn = new Function(qApp, tokens[i].getToken());
    expectTokenType(tokens,i-1,Token::Int32Type);
    i+=2;
    expectTokenType(tokens,i,Token::StringType);
    expectTokenType(tokens,++i,Token::OpeningBracket);
    expectTokenType(tokens,++i,Token::ClosingBracket);
    expectTokenType(tokens,++i,Token::Identifier);
     expectTokenType(tokens,++i,Token::ClosingParenthesis);
    expectTokenType(tokens,++i,Token::OpeningBrace);
    parseInstructions(mainFn,tokens,++i);
    return mainFn;
}

void Parser::parseInstructions(InstructionBlock *instrBlock, TokenList &tokens, qsizetype & currentPos)
{
    for(qsizetype i=currentPos;i<tokens.size();++i)
    {
        qDebug().noquote()<<tokens[i].getToken() <<" | "<< Token::tokenTypeToString(tokens.secureAccess(i).getType());
        switch (tokens[i].getType()) {
        case Token::ClosingBrace:
        {
            currentPos = i+1;
            return;
        }
        case Token::Assign:
        {
//             Expression*  expr(nullptr);
            Expression*  other = getExpression(tokens,i+1,instrBlock);
           // bool declare=false;
            if(checkTokenType(tokens,i-2,getTypeTokens() ))
            {
//                declare=true;

                DeclareInstruction * instr=new DeclareInstruction(qApp,instrBlock,Var::create( qApp,Type::typeForName(getTokenAndExpectTokenType(tokens,i-2,getTypeTokens() )),getTokenAndExpectTokenType(tokens,i-1,Token::Identifier)),other);
                instrBlock->addInstruction(instr);
            } else {
                AssignInstruction * instr=new AssignInstruction(qApp,instrBlock,getTokenAndExpectTokenType(tokens,i-1,Token::Identifier),other);
                instrBlock->addInstruction(instr);
            }


            /*instrBlock->addInstruction([expr,other,instrBlock,declare]() {
                if(expr)
                {
                    if(other)
                    {
                        if(declare)
                        {
                            instrBlock->declareVariable(static_cast<Var*>(expr));
                        }

                        expr->assign(other);
                    } else{
                        delete expr;
                        throwExceptionWithLine("");
                    }

                }

            });*/
            break;
        }
        case Token::ForLoop:
        {
            expectTokenType(tokens,++i,Token::OpeningParenthesis);
            Instruction * start=nullptr;
            if(tokens.secureAccessType(i+3) == Token::Assign && checkTokenType(tokens,i+1,getTypeTokens() ))
            {
                auto var=Var::create(qApp,Type::typeForName(tokens[i+1].getToken()),tokens[i+2].getToken());
                start = new DeclareInstruction(qApp,instrBlock,var,getExpression(tokens,i+4,instrBlock));
                i+=5;
                expectTokenType(tokens,i,Token::Semicolon);
            } else if (tokens.secureAccessType(i+2) == Token::Assign)
            {
                start = new AssignInstruction(qApp,instrBlock,tokens[i+1].getToken(), getExpression(tokens,i+3,instrBlock));
            } else {
                throwExceptionWithLine("unsupported");
            }

            Expression*  cond = getExpression(tokens,i+1,instrBlock);
            i+=3;
            Instruction * step=nullptr;

            if(tokens.secureAccessType(i+1) == Token::Increment) {
                tokens.removeAt(i+1);
                step = new IncrementInstruction(qApp,instrBlock, getExpression(tokens,i,instrBlock));
            }


            instrBlock->addInstruction(new ForLoop(qApp,instrBlock, start,cond,step));
            break;
        }
        case Token::WhileLoop:
        {
            expectTokenType(tokens,++i,Token::OpeningParenthesis);
            Expression*  cond = getExpression(tokens,i+1,instrBlock);
            auto whileloop=new WhileLoop(qApp,instrBlock, cond);

            instrBlock->addInstruction(whileloop);
            i+=2;
            expectTokenType(tokens ,i++, Token::ClosingParenthesis);
            expectTokenType(tokens ,i++, Token::OpeningBrace);
            parseInstructions(whileloop,tokens,i);
            break;
        }
        case Token::Increment:
        {
            instrBlock->addInstruction(new IncrementInstruction(qApp,instrBlock, getExpression(tokens,i-1,instrBlock)));
            break;
        }
        case Token::DebugFunction:
        {
            expectTokenType(tokens ,++i, Token::OpeningParenthesis);
            instrBlock->addInstruction(new DebugFunction(qApp,instrBlock, getExpression(tokens,++i,instrBlock)));
            expectTokenType(tokens ,++i, Token::ClosingParenthesis);
            break;
        }
        default:
            break;
        }
    }

    //qDebug()<<tokens[i].getToken();
}

Expression*   Parser::getPlainExpression(TokenList &tokens, qsizetype pos, InstructionBlock *instrBlock)
{
#ifdef QT_DEBUG
    TokenList original(tokens);
#endif

    for(qsizetype i=pos;i<tokens.size()-1;++i)
    {
        if(tokens[i].getType()==Token::Semicolon || tokens[i].getType() == Token::ClosingParenthesis) {
            break;
        }
        switch (tokens[i].getType()) {

        case Token::Not:
        {
//            tokens[i].setExpr(make_shared<NotOperator>(tokens[i+1].getExpr()));
//            tokens.secureRemoveAt(i+1);
//            break;
        }
        case Token::Minus:
        {
            if(i>0)
            {
                switch (tokens[i-1].getType()) {
                case Token::Minus:
                case Token::Plus:
                case Token::Divide:
                case Token::Multiply:
                case Token::GreaterThan:
                case Token::GreaterThanOrEqual:
                case Token::LessThan:
                case Token::LessThanOrEqual:
                case Token::Or:
                case Token::And:
                case Token::Not:
                case Token::NotEquals:
                    tokens[i].setExpr(new UnaryMinusOperator(qApp,tokens[i+1].getExpr()));
                    tokens[i].setType(Token::UnaryMinus);
                    tokens.secureRemoveAt(i+1);
                    break;
                default:
                    break;
                }
            }
            else
            {
                tokens[i].setExpr(new UnaryMinusOperator(qApp,tokens[i+1].getExpr()));
                tokens[i].setType(Token::UnaryMinus);
                tokens.secureRemoveAt(i+1);
            }
            break;
        }
        case Token::Plus:
        {
            if(i>0)
            {
                switch (tokens[i-1].getType()) {
                case Token::Minus:
                case Token::Plus:
                case Token::Divide:
                case Token::Multiply:
                case Token::GreaterThan:
                case Token::GreaterThanOrEqual:
                case Token::LessThan:
                case Token::LessThanOrEqual:
                case Token::Or:
                case Token::And:
                case Token::Not:
                case Token::NotEquals:
                    tokens.secureRemoveAt(i);
                    break;
                default:
                    break;
                }
            }
            else
            {
                tokens.secureRemoveAt(i);
            }
            break;
        }
        default:
            break;
        }
    }

    for(qsizetype i=pos+1;i<tokens.size()-1;++i)
    {
        if(tokens[i].getType()==Token::Semicolon || tokens[i].getType() == Token::ClosingParenthesis) {
            break;
        }
        switch (tokens[i].getType()) {
        case Token::Multiply:
        {
            tokens[i].setExpr(new MultiplyOperator(qApp, tokens[i-1].getExpr(),tokens[i+1].getExpr()));
            tokens.secureRemoveAt(--i);
            tokens.secureRemoveAt(i+1);
            break;
        }
        case Token::Divide:
        {
            tokens[i].setExpr(new DivideOperator(qApp,tokens[i-1].getExpr(),tokens[i+1].getExpr()));
            tokens.secureRemoveAt(--i);
            tokens.secureRemoveAt(i+1);
            break;
        }
        default:
            break;
        }
    }
    for(qsizetype i=pos+1;i<tokens.size()-1;++i)
    {
        if(tokens[i].getType()==Token::Semicolon || tokens[i].getType() == Token::ClosingParenthesis) {
            break;
        }
        switch (tokens[i].getType()) {
        case Token::Plus:
        {
            tokens[i].setExpr(new PlusOperator(qApp,tokens[i-1].getExpr(),tokens[i+1].getExpr()));
            tokens.secureRemoveAt(--i);
            tokens.secureRemoveAt(i+1);
            break;
        }
        case Token::Minus:
        {
            tokens[i].setExpr(new MinusOperator(qApp,tokens[i-1].getExpr(),tokens[i+1].getExpr()));
            tokens.secureRemoveAt(--i);
            tokens.secureRemoveAt(i+1);
            break;
        }
        default:
            break;
        }
    }
    for(qsizetype i=pos;i<tokens.size()-1;++i)
    {
        if(tokens[i].getType() == Token::Identifier)
        {
            tokens[i].setExpr(new AccessVarExpression(qApp,instrBlock, tokens[i].getToken()));
        }
    }
    for(qsizetype i=pos+1;i<tokens.size()-1;++i)
    {
        if(tokens[i].getType()==Token::Semicolon || tokens[i].getType() == Token::ClosingParenthesis) {
            break;
        }
        switch (tokens[i].getType()) {
      case Token::GreaterThan:
        {
            tokens[i].setExpr(new GreaterThanOperator(qApp, tokens[i-1].getExpr(),tokens[i+1].getExpr()));
            tokens.secureRemoveAt(--i);
            tokens.secureRemoveAt(i+1);
            break;
        }
          /*case Token::GreaterThanOrEqual:
        {
            tokens[i].setExpr(make_shared<ComparisonOperator>(tokens[i-1].getExpr(),tokens[i+1].getExpr(),QList<QPartialOrdering>()
                                                                                                                    << QPartialOrdering::Greater
                                                                                                                    << QPartialOrdering::Equivalent));
            tokens.secureRemoveAt(--i);
            tokens.secureRemoveAt(i+1);
            break;
        }*/
        case Token::LessThan:
        {
            tokens[i].setExpr(new LessThanOperator(qApp, tokens[i-1].getExpr(),tokens[i+1].getExpr()));
            tokens.secureRemoveAt(--i);
            tokens.secureRemoveAt(i+1);
            break;
        }
        /*case Token::LessThanOrEqual:
        {
            tokens[i].setExpr(make_shared<ComparisonOperator>(tokens[i-1].getExpr(),tokens[i+1].getExpr(),QList<QPartialOrdering>()
                                                                                                                    << QPartialOrdering::Less
                                                                                                                    << QPartialOrdering::Equivalent));
            tokens.secureRemoveAt(--i);
            tokens.secureRemoveAt(i+1);
            break;
        }
        case Token::NotEquals:
        {
            tokens[i].setExpr(make_shared<ComparisonOperator>(tokens[i-1].getExpr(),tokens[i+1].getExpr(),QList<QPartialOrdering>()
                                                                                                                    << QPartialOrdering::Less
                                                                                                                    << QPartialOrdering::Greater));
            tokens.secureRemoveAt(--i);
            tokens.secureRemoveAt(i+1);
            break;
        }
        case Token::Equals:
        {
            tokens[i].setExpr(make_shared<ComparisonOperator>(tokens[i-1].getExpr(),tokens[i+1].getExpr(), QPartialOrdering::Equivalent));
            tokens.secureRemoveAt(--i);
            tokens.secureRemoveAt(i+1);
            break;
        }*/
        default:
            break;
        }
    }

    if(tokens.isEmpty())
    {
        throwExceptionWithLine("syntax error. tokens empty");
    } else if( tokens.size()<pos )
    {
        throwExceptionWithLine("syntax error. unexpected eof");
    } else if(  tokens[pos].getExpr()==nullptr)
    {
        throwExceptionWithLine(QStringLiteral("syntax error. Expr at pos %1 is null").arg(pos));
    }
    return tokens[pos].getExpr();
}




AST * Parser::parse(const QString &s)
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
                     if(getChar(s,i+1)=='+') {
                        addToken(s,tokens,start,i,Token::Increment,1);
                     } else {
                        addToken(s,tokens,start,i,Token::Plus);
                     }

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
                     if(getChar(s,i+1)=='/') {
#ifdef QT_DEBUG
                        //qDebug().noquote()<<"comment at pos "<<i;
                        //auto k=i+2;
#endif
                        while(i<s.length())
                        {
                            ++i;
                            if(s[i]=='\n') {
                                start =i;
#ifdef QT_DEBUG
                              //  qDebug().noquote()<<"ignored comment "<<s.mid(k,i-k-1);
#endif
                                break;
                            }
                        }

                     } else {
                        addToken(s,tokens,start,i,Token::Divide);
                     }

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
                    addToken(s,tokens,start,i,Token::OpeningBracket);
                    break;
                }
                case ']':
                {
                     addToken(s,tokens,start,i,Token::ClosingBracket);
                     break;
                }
                case '>':
                {
                     switch (getChar(s,i+1)) {
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
                     break;
                }
                case '<':
                {
                     switch (getChar(s,i+1)) {
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
                     break;
                }
                case '!':
                {
                     switch (getChar(s,i+1)) {
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
                     break;
                }
                case '=':
                {
                     switch (getChar(s,i+1)) {
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
                         tokens.append(Token(str, Token::StringLiteral, new StringConstant(qApp,str)));
                         start=i+1;
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
   // for(const Token &t:tokens)
   // {
        //qDebug().noquote()<<t.getToken()<<":  "<<t.getType();
       // qDebug()<<"---------------";
    //}
#endif

    auto ast = new AST(qApp);
    parseRoot(ast,tokens);
    //return buildAST(tokens);
    return ast;
}

char Parser::getChar(const QString & s, qsizetype i)
{
    if(i>=s.size())
    {
        throwExceptionWithLine(QStringLiteral("syntax error at pos %1: unexpected end").arg(i));
    }
    return s[i].toLatin1();
}

