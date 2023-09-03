#include "tokenlist.h"
#include "exception/qtexception.h"
#include "token.h"
qsizetype TokenList::getPos() const
{
    return pos;
}

void TokenList::secureRemoveAt(qsizetype i)
{
    if(i>=0 && i<size())
    {
        removeAt(i);
    } else {
        throwExceptionWithLine("syntax error");
    }

}

const Token & TokenList::secureAccess(qsizetype i)const
{
    if(i>=0 && i<size())
    {
        return (*this)[i];
    } else {
        throwExceptionWithLine("syntax error");
    }
}
const QString & TokenList::secureAccessStr(qsizetype i) const
{
    if(i>=0 && i<size())
    {
        return (*this)[i].getToken();
    } else {
        throwExceptionWithLine("syntax error");
    }
}

Token::TokenType TokenList::secureAccessType(qsizetype i)const
{
    if(i>=0 && i<size())
    {
        return (*this)[i].getType();
    } else {
        throwExceptionWithLine("syntax error");
    }
}

TokenList::TokenList() : pos(-1)
{

}

TokenList::TokenList(const QList<Token> &tokens)
{
    append(tokens.begin(),tokens.end());
}

TokenList &TokenList::incr()
{
    ++pos;
    return *this;
}

TokenList &TokenList::offset(int offset)
{
    pos += offset;
    return *this;
}

TokenList & TokenList::decr()
{
    --pos;
    return *this;
}


const Token& TokenList::nextToken()
{
    if( (++pos) < this->size())
    {
        return (*this)[pos];
    }
    throwExceptionWithLine("syntax error");
}

const Token &TokenList::peekCurrToken()const
{
    if( pos < size())
    {
        return (*this)[pos];
    }
    throwExceptionWithLine("syntax error");
}

Token::TokenType TokenList::peekCurrTokenType() const
{
    return peekNextToken().getType();
}

const Token &TokenList::peekNextToken()const
{
    if( pos < size())
    {
        return (*this)[pos+1];
    }
    throwExceptionWithLine("syntax error");
}

Token::TokenType TokenList::peekNextTokenType() const
{
    return peekNextToken().getType();
}

const Token &TokenList::peekToken(int offset)const
{
    if( pos+offset < size())
    {
        return (*this)[pos+offset];
    }
    throwExceptionWithLine("syntax error");
}

const QString &TokenList::peekTokenStr() const
{
    return peekCurrToken().getToken();
}


const QString &TokenList::peekTokenStr(int offset) const
{
    return peekToken(offset).getToken();
}

bool TokenList::incrIfNextTokenEquals(Token::TokenType t)
{
    if(peekNextToken().getType() == t)
    {
        incr();
        return true;
    }
    return false;
}

bool TokenList::incrIfNextTokenNotEquals(Token::TokenType t)
{
    if(peekNextToken().getType() != t)
    {
        incr();
        return true;
    }
    return false;
}


bool TokenList::hasNext() const
{
    return pos < size()-1;
}



const QRegularExpression TokenList::INT_EXPRESSION("^\\d+$");
const QRegularExpression TokenList::FLOAT_EXPRESSION("^\\d+\\.\\d+$");

