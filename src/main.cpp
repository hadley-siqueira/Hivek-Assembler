#include <iostream>
#include <vector>

#include "HivekAssembler/HivekAssembler.h"
#include "lex/Lex.h"
#include <token/Token.h>

using namespace HivekAssembler;

void text_lex() {
    HivekAssembler::Lex lex;
    std::vector<Token> tokens;
    tokens = lex.read("/tmp/foo.s");

    for (int i = 0; i < tokens.size(); ++i) {
        std::cout << tokens[i].to_str() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    /*HivekAssembler::HivekAssembler assembler;

    assembler.open(argv[1]);
    assembler.assemble();
    assembler.write("out.bin");*/
    text_lex();

    return 0;
}
