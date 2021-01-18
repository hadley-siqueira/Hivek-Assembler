#ifndef HIVEK_ASSEMBLER_PARSER_H
#define HIVEK_ASSEMBLER_PARSER_H

#include <vector>
#include <string>
#include <map>

#include "token/Token.h"
#include "commands/Command.h"
#include "HivekDefs.h"

namespace HivekAssembler {
    class Parser {
    public:
        Parser();

    public:
        std::vector<Command*> read(std::string path);

    private:
        void parse_program();
        void parse_directive();
        void parse_instruction();

    private:
        bool match(TokenKind kind);
        bool lookeahed(TokenKind kind);
        bool expect(TokenKind kind);
        bool hasNext();
        void advance();

    private:
        std::vector<Token> tokens;
        std::vector<Command*> commands;
        std::map<std::string, Opcode> opcode_map;
        std::map<std::string, int> reg_map;
        int current_token_idx;
        Token matched;
    };
}

#endif
