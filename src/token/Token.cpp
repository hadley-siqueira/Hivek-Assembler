#include "token/Token.h"

using namespace HivekAssembler;

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
