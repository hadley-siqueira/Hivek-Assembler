#ifndef HIVEK_ASSEMBLER_LEX_H
#define HIVEK_ASSEMBLER_LEX_H

#include <vector>
#include <map>
#include <fstream>

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
        std::map<std::string, TokenKind> token_map;
        std::map<std::string, TokenKind> reg_map;
    };
}

#endif
