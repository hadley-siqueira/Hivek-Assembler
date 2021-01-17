#ifndef HIVEK_ASSEMBLER_TOKEN_H
#define HIVEK_ASSEMBLER_TOKEN_H

#include <string>

namespace HivekAssembler {
    typedef enum TokenKind {
        // opcodes
        TK_ADD,
        TK_SUB,
        TK_BEQ,

        TK_32_ADDI,

        // operators
        TK_COMMA,
        TK_COLON,
        TK_DOT,
        TK_UNARY_MINUS,

        // others
        TK_IDENTIFIER,
        TK_NUMBER
    } TokenKind;

    class Token {
    public:
        Token(TokenKind kind, int line, int column);
        Token(TokenKind kind, int line, int column, std::string lexem);

    private:
        TokenKind kind;
        int line;
        int column;
        std::string lexem;
    };
}

#endif
