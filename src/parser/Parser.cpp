#include <iostream>
#include <sstream>

#include "parser/Parser.h"
#include "lex/Lex.h"
#include "commands/Command.h"
#include "commands/label/Label.h"
#include "commands/instructions/Instruction.h"

using namespace HivekAssembler;

Parser::Parser() {
    opcode_map["add"] = OPCODE_24_ADD;
    opcode_map["sub"] = OPCODE_24_SUB;

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

    return commands;
}

void Parser::parse_program() {
    Token token;
    Command* command;

    while (!match(TK_EOF)) {
        if (match(TK_IDENTIFIER)) {
            token = matched;

            if (match(TK_COLON)) {
                command = new Label(token);
                commands.push_back(command);
            } else {
                parse_instruction();
            }
        } else if (lookeahed(TK_DOT)) {
            parse_directive();
        }
    }
}

void Parser::parse_directive() {

}

void Parser::parse_instruction() {
    Opcode opcode;
    Token ra;
    Token rb;
    Token rc;
    Token immd;

    if (opcode_map.count(matched.getLexem()) == 0) {
        std::cout << "Error parsing instruction\n";
        exit(0);
    }

    opcode = opcode_map[matched.getLexem()];

    switch (opcode) {
    case OPCODE_24_ADD:
    case OPCODE_24_SUB:
    case OPCODE_24_AND:
    case OPCODE_24_OR:
        expect(TK_IDENTIFIER);
        rc = matched;

        expect(TK_COMMA);
        expect(TK_IDENTIFIER);
        ra = matched;

        expect(TK_COMMA);
        expect(TK_IDENTIFIER);
        rb = matched;

        commands.push_back(new Instruction(opcode, ra, rb, rc));
        break;
    default:
        break;
    }

}

bool Parser::match(TokenKind kind) {
    if (lookeahed(kind)) {
        advance();
        return true;
    }

    return false;
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
