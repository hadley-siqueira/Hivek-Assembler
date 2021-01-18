#include <iostream>
#include <fstream>
#include <sstream>

#include "lex/Lex.h"

using namespace HivekAssembler;

std::vector<Token> Lex::read(std::string path) {
    int c;
    std::vector<Token> result;

    line = 1;
    column = 1;
    file.open(path.c_str());

    while (file.good()) {
        c = file.get();

        if (c == '.') {
            result.push_back(Token(TK_DOT, line, column, "."));
            ++column;
        } else if (c == ',') {
            result.push_back(Token(TK_COMMA, line, column, ","));
            ++column;
        } else if (c == ':') {
            result.push_back(Token(TK_COLON, line, column, ":"));
            ++column;
        } else if (c == '-') {
            result.push_back(Token(TK_UNARY_MINUS, line, column, "-"));
            ++column;
        } else if (c == '(') {
            result.push_back(Token(TK_LEFT_PARENTHESIS, line, column, "("));
            ++column;
        } else if (c == ')') {
            result.push_back(Token(TK_RIGHT_PARENTHESIS, line, column, ")"));
            ++column;
        } else if (isalpha(c) || c == '_') {
            int old_column = column;
            std::stringstream lexem;

            lexem << (char) c;
            ++column;

            while (isalnum(file.peek()) || file.peek() == '_') {
                lexem << (char) file.get();
                ++column;
            }

            result.push_back(Token(TK_IDENTIFIER, line, old_column, lexem.str()));
        } else if (isdigit(c)) {
            int old_column = column;
            std::stringstream lexem;

            lexem << (char) c;
            ++column;

            if (file.peek() == 'b' || file.peek() == 'o' || file.peek() == 'x') {
                lexem << (char) file.get();
                ++column;
            }

            while (isdigit(file.peek())) {
                lexem << (char) file.get();
                ++column;
            }

            result.push_back(Token(TK_NUMBER, line, old_column, lexem.str()));
        } else if (c == '"') {
            int old_column = column;
            std::stringstream lexem;

            c = file.get();

            while (c != '"') {
                if (c == '\\') {
                    lexem << (char) c;
                    c = file.get();
                    ++column;
                }

                lexem << (char) c;
                c = file.get();
                ++column;
            }

            result.push_back(Token(TK_STRING, line, old_column, lexem.str()));
        } else if (c == '\n') {
            ++line;
            column = 1;
        } else if (c == '#') {
            while (file.peek() != '\n') {
                file.get();
            }
        } else {
            ++column;
        }
    }

    result.push_back(Token(TK_EOF, line, column));
    file.close();
    return result;
}
