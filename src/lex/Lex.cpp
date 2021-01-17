#include <fstream>
#include <sstream>

#include "lex/Lex.h"

using namespace HivekAssembler;

Lex::Lex() {
    opcode_map["addi"] = TK_32_ADDI;
}

std::vector<Token> Lex::read(std::string path) {
    int c;
    std::vector<Token> result;

    line = 1;
    column = 1;
    file.open(path.c_str());

    while (file.good()) {
        c = file.get();

        if (c == '.') {
            result.push_back(Token(TK_DOT, line, column));
            ++column;
        } else if (c == ',') {
            result.push_back(Token(TK_COMMA, line, column));
            ++column;
        } else if (c == ':') {
            result.push_back(Token(TK_COLON, line, column));
            ++column;
        } else if (c == '-') {
            result.push_back(Token(TK_UNARY_MINUS, line, column));
            ++column;
        } else if (isalpha(c)) {
            int old_column = column;
            std::stringstream lexem;

            lexem << (char) c;
            ++column;

            while (isalnum(file.peek())) {
                lexem << (char) file.get();
                ++column;
            }

            if (opcode_map.count(lexem.str()) > 0) {
                TokenKind kind = opcode_map[lexem.str()];

                result.push_back(Token(kind, line, old_column));
            } else {
                result.push_back(Token(TK_IDENTIFIER, line, column, lexem.str()));
            }
        } else if (isdigit(c)) {
            int old_column = column;
            std::stringstream lexem;

            lexem << (char) c;
            ++column;

            while (isdigit(file.peek())) {
                lexem << (char) file.get();
                ++column;
            }

            result.push_back(Token(TK_NUMBER, line, column, lexem.str()));
        } else if (c == '\n') {
            ++line;
        }
    }

    file.close();
    return result;
}
