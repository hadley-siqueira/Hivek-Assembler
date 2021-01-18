#include <sstream>

#include "token/Token.h"

using namespace HivekAssembler;

Token::Token() {

}

Token::Token(TokenKind kind, int line, int column) {
    this->kind = kind;
    this->line = line;
    this->column = column;
}

Token::Token(TokenKind kind, int line, int column, std::string lexem) {
    this->kind = kind;
    this->line = line;
    this->column = column;
    this->lexem = lexem;
}

std::string Token::to_str() {
    std::stringstream s;

    s << "(" << lexem << ", " << line << ", " << column << ")";

    return s.str();
}

TokenKind Token::getKind() const
{
    return kind;
}

void Token::setKind(const TokenKind &value)
{
    kind = value;
}

int Token::getLine() const
{
    return line;
}

void Token::setLine(int value)
{
    line = value;
}

int Token::getColumn() const
{
    return column;
}

void Token::setColumn(int value)
{
    column = value;
}

std::string Token::getLexem() const
{
    return lexem;
}

void Token::setLexem(const std::string &value)
{
    lexem = value;
}
