#ifndef HIVEK_ASSEMBLER_LEX_H
#define HIVEK_ASSEMBLER_LEX_H

#include <vector>
#include <fstream>
#include <map>

#include "HivekDefs.h"
#include "token/Token.h"

namespace HivekAssembler {
    class Lex {
    public:
        Lex();

    public:
        std::vector<Token> read(std::string path);

    private:
        std::ifstream file;
        int line;
        int column;
        std::map<std::string, TokenKind> opcode_map;
    };
}

#endif
