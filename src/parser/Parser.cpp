#include <iostream>
#include <sstream>

#include "parser/Parser.h"
#include "lex/Lex.h"
#include "commands/Command.h"
#include "commands/label/Label.h"
#include "commands/instructions/Instruction.h"

using namespace HivekAssembler;

Parser::Parser() {
    opcode_map[TK_ADD] = OPCODE_24_ADD;
    opcode_map[TK_SUB] = OPCODE_24_SUB;
    opcode_map[TK_AND] = OPCODE_24_AND;

    for (int i = 0; i < 32; ++i) {
        std::stringstream s;

        s << "r" << i;
        reg_map[s.str()] = i;
    }
}

std::vector<Command*> Parser::read(std::string path) {
    Lex lex;

    current_token_idx = 0;
    tokens = lex.read(path);

    parse_program();

    return commands;
}

void Parser::parse_program() {
    Token token;
    Command* command;

    while (!match(TK_EOF)) {
        if (match(TK_IDENTIFIER)) {
            token = matched;

            expect(TK_COLON);
            command = new Label(token);
            commands.push_back(command);
        } else if (lookeahed(TK_DOT)) {
            parse_directive();
        } else {
            parse_instruction();
        }
    }
}

void Parser::parse_directive() {

}

void Parser::parse_instruction() {
    TokenKind kind;
    Token opcode;
    Token ra;
    Token rb;
    Token rc;
    Token immd;
    bool make_neg = false;

    match();
    opcode = matched;
    kind = matched.getKind();

    switch (kind) {
    case TK_ADD:
    case TK_SUB:
    case TK_AND:
    case TK_OR:
    case TK_XOR:
        parse_integer_register();
        rc = matched;

        expect(TK_COMMA);
        parse_integer_register();
        ra = matched;

        expect(TK_COMMA);
        parse_integer_register();
        rb = matched;

        commands.push_back(new Instruction(opcode, ra, rb, rc));
        break;

    case TK_ADDI:
    case TK_ANDI:
    case TK_ORI:
    case TK_BEQ:
    case TK_BNE:
    case TK_BLT:
    case TK_BGE:
        parse_integer_register();
        ra = matched;

        expect(TK_COMMA);
        parse_integer_register();
        rb = matched;

        expect(TK_COMMA);

        if (match(TK_UNARY_MINUS)) {
            make_neg = true;
        }

        if (match(TK_NUMBER)) {
            immd = matched;
        } else if (match(TK_IDENTIFIER)) {
            immd = matched;
        } else {
            std::cout << "Error parsing ri instruction\n";
            exit(0);
        }

        if (make_neg) {
            immd.makeNegative();
        }

        commands.push_back(new Instruction(opcode, ra, rb, immd));
        break;

    case TK_LD:
    case TK_LW:
    case TK_LH:
    case TK_LB:
    case TK_LWU:
    case TK_LHU:
    case TK_LBU:
    case TK_SD:
    case TK_SW:
    case TK_SH:
    case TK_SB:
        parse_integer_register();
        rb = matched;

        expect(TK_COMMA);

        if (match(TK_UNARY_MINUS)) {
            make_neg = true;
        }

        if (match(TK_NUMBER)) {
            immd = matched;
        } else if (match(TK_IDENTIFIER)) {
            immd = matched;
        } else {
            std::cout << "Error parsing ri instruction\n";
            exit(0);
        }

        if (make_neg) {
            immd.makeNegative();
        }

        expect(TK_LEFT_PARENTHESIS);
        parse_integer_register();
        ra = matched;
        expect(TK_RIGHT_PARENTHESIS);
        commands.push_back(new Instruction(opcode, ra, rb, immd));
        break;

    default:
        std::cout << "Invalid instruction\n";
        exit(0);
        break;
    }

}

void Parser::parse_integer_register() {
    if (match(TK_R0)) return;
    if (match(TK_R1)) return;
    if (match(TK_R2)) return;
    if (match(TK_R3)) return;
    if (match(TK_R4)) return;
    if (match(TK_R5)) return;
    if (match(TK_R6)) return;
    if (match(TK_R7)) return;
    if (match(TK_R8)) return;
    if (match(TK_R9)) return;
    if (match(TK_R10)) return;
    if (match(TK_R11)) return;
    if (match(TK_R12)) return;
    if (match(TK_R13)) return;
    if (match(TK_R14)) return;
    if (match(TK_R15)) return;
    if (match(TK_R16)) return;
    if (match(TK_R17)) return;
    if (match(TK_R18)) return;
    if (match(TK_R19)) return;
    if (match(TK_R20)) return;
    if (match(TK_R21)) return;
    if (match(TK_R22)) return;
    if (match(TK_R23)) return;
    if (match(TK_R24)) return;
    if (match(TK_R25)) return;
    if (match(TK_R26)) return;
    if (match(TK_R27)) return;
    if (match(TK_R28)) return;
    if (match(TK_R29)) return;
    if (match(TK_R30)) return;
    if (match(TK_R31)) return;

    std::cout << "Error parsing integer register\n";
    exit(0);
}

bool Parser::match(TokenKind kind) {
    if (lookeahed(kind)) {
        advance();
        return true;
    }

    return false;
}

bool Parser::match() {
    advance();
    return true;
}

bool Parser::lookeahed(TokenKind kind) {
    if (hasNext()) {
        return tokens[current_token_idx].getKind() == kind;
    }

    return false;
}

bool Parser::expect(TokenKind kind) {
    if (!match(kind)) {
        std::cout << "Error while parsing\n";
        exit(0);
    }

    return true;
}

bool Parser::hasNext() {
    return current_token_idx < tokens.size();
}

void Parser::advance() {
    matched = tokens[current_token_idx];
    current_token_idx += 1;
}
