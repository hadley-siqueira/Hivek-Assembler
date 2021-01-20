#ifndef HIVEK_ASSEMBLER_TOKEN_H
#define HIVEK_ASSEMBLER_TOKEN_H

#include <string>

namespace HivekAssembler {
    typedef enum TokenKind {
        // instructions
        TK_ADD,
        TK_SUB,
        TK_AND,
        TK_OR,
        TK_XOR,

        TK_ADDI,
        TK_ANDI,
        TK_ORI,
        TK_XORI,

        TK_BEQ,
        TK_BNE,
        TK_BLT,
        TK_BGE,

        TK_LD,
        TK_LW,
        TK_LH,
        TK_LB,
        TK_LWU,
        TK_LHU,
        TK_LBU,

        TK_SD,
        TK_SW,
        TK_SH,
        TK_SB,

        // registers
        TK_R0,
        TK_R1,
        TK_R2,
        TK_R3,
        TK_R4,
        TK_R5,
        TK_R6,
        TK_R7,
        TK_R8,
        TK_R9,
        TK_R10,
        TK_R11,
        TK_R12,
        TK_R13,
        TK_R14,
        TK_R15,
        TK_R16,
        TK_R17,
        TK_R18,
        TK_R19,
        TK_R20,
        TK_R21,
        TK_R22,
        TK_R23,
        TK_R24,
        TK_R25,
        TK_R26,
        TK_R27,
        TK_R28,
        TK_R29,
        TK_R30,
        TK_R31,

        // operators
        TK_COMMA,
        TK_COLON,
        TK_DOT,
        TK_UNARY_MINUS,
        TK_LEFT_PARENTHESIS,
        TK_RIGHT_PARENTHESIS,

        // others
        TK_IDENTIFIER,
        TK_NUMBER,
        TK_STRING,
        TK_EOF
    } TokenKind;

    class Token {
    public:
        Token();
        Token(TokenKind kind, int line, int column);
        Token(TokenKind kind, int line, int column, std::string lexem);

    public:
        std::string to_str();

        TokenKind getKind() const;
        void setKind(const TokenKind &value);

        int getLine() const;
        void setLine(int value);

        int getColumn() const;
        void setColumn(int value);

        std::string getLexem() const;
        void setLexem(const std::string &value);

    private:
        TokenKind kind;
        int line;
        int column;
        std::string lexem;
    };
}

#endif
