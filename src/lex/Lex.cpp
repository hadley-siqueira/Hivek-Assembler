#include <iostream>
#include <fstream>
#include <sstream>

#include "lex/Lex.h"

using namespace HivekAssembler;

Lex::Lex() {
    token_map["add"] = TK_ADD;
    token_map["sub"] = TK_SUB;
    token_map["and"] = TK_AND;
    token_map["or"] = TK_OR;
    token_map["xor"] = TK_XOR;

    token_map["addi"] = TK_ADDI;
    token_map["andi"] = TK_ANDI;
    token_map["ori"] = TK_ORI;
    token_map["xori"] = TK_XORI;

    token_map["beq"] = TK_BEQ;
    token_map["bne"] = TK_BNE;
    token_map["blt"] = TK_BLT;
    token_map["bge"] = TK_BGE;

    token_map["ld"] = TK_LD;
    token_map["lw"] = TK_LW;
    token_map["lh"] = TK_LH;
    token_map["lb"] = TK_LB;
    token_map["lwu"] = TK_LWU;
    token_map["lhu"] = TK_LHU;
    token_map["lbu"] = TK_LBU;

    token_map["sd"] = TK_SD;
    token_map["sw"] = TK_SW;
    token_map["sh"] = TK_SH;
    token_map["sb"] = TK_SB;

    // registers
    reg_map["r0"] = TK_R0;
    reg_map["r1"] = TK_R1;
    reg_map["r2"] = TK_R2;
    reg_map["r3"] = TK_R3;
    reg_map["r4"] = TK_R4;
    reg_map["r5"] = TK_R5;
    reg_map["r6"] = TK_R6;
    reg_map["r7"] = TK_R7;
    reg_map["r8"] = TK_R8;
    reg_map["r9"] = TK_R9;
    reg_map["r10"] = TK_R10;
    reg_map["r11"] = TK_R11;
    reg_map["r12"] = TK_R12;
    reg_map["r13"] = TK_R13;
    reg_map["r14"] = TK_R14;
    reg_map["r15"] = TK_R15;
    reg_map["r16"] = TK_R16;
    reg_map["r17"] = TK_R17;
    reg_map["r18"] = TK_R18;
    reg_map["r19"] = TK_R19;
    reg_map["r20"] = TK_R20;
    reg_map["r21"] = TK_R21;
    reg_map["r22"] = TK_R22;
    reg_map["r23"] = TK_R23;
    reg_map["r24"] = TK_R24;
    reg_map["r25"] = TK_R25;
    reg_map["r26"] = TK_R26;
    reg_map["r27"] = TK_R27;
    reg_map["r28"] = TK_R28;
    reg_map["r29"] = TK_R29;
    reg_map["r30"] = TK_R30;
    reg_map["r31"] = TK_R31;
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

            if (token_map.count(lexem.str()) > 0) {
                TokenKind kind = token_map[lexem.str()];
                result.push_back(Token(kind, line, old_column, lexem.str()));
            } else if (reg_map.count(lexem.str()) > 0) {
                TokenKind kind = reg_map[lexem.str()];
                result.push_back(Token(kind, line, old_column, lexem.str()));
            } else {
                result.push_back(Token(TK_IDENTIFIER, line, old_column, lexem.str()));
            }
        } else if (isdigit(c)) {
            int old_column = column;
            std::stringstream lexem;

            lexem << (char) c;
            ++column;
            bool is_zero = c == '0';

            if (is_zero && file.peek() == 'b') {
                lexem << (char) file.get();
                ++column;

                while (file.peek() == '0' || file.peek() == '1') {
                    lexem << (char) file.get();
                    ++column;
                }
            } else if (is_zero && file.peek() == 'o') {
                lexem << (char) file.get();
                ++column;

                while (file.peek() >= '0' && file.peek() <= '7') {
                    lexem << (char) file.get();
                    ++column;
                }
            } else if (is_zero && file.peek() == 'x') {
                lexem << (char) file.get();
                ++column;

                while (isdigit(file.peek()) || (file.peek() >= 'a' && file.peek() <= 'f') || (file.peek() >= 'A' && file.peek() <= 'F'))  {
                    lexem << (char) file.get();
                    ++column;
                }
            } else {
                while (isdigit(file.peek())) {
                    lexem << (char) file.get();
                    ++column;
                }
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
