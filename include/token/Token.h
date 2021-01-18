#ifndef HIVEK_ASSEMBLER_TOKEN_H
#define HIVEK_ASSEMBLER_TOKEN_H

#include <string>

namespace HivekAssembler {
    typedef enum TokenKind {
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
