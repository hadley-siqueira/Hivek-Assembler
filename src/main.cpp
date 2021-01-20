#include <iostream>
#include <vector>

#include "HivekAssembler/HivekAssembler.h"
#include "lex/Lex.h"
#include "parser/Parser.h"
#include <token/Token.h>

using namespace HivekAssembler;

void text_lex() {
    HivekAssembler::Lex lex;
    std::vector<Token> tokens;
    tokens = lex.read("foo.s");

    for (int i = 0; i < tokens.size(); ++i) {
        std::cout << tokens[i].to_str() << std::endl;
    }
}

void test_parser() {
    Parser parser;
    std::vector<Command*> cmds;

    cmds = parser.read("foo.s");

    std::cout << "print cmd\n";
    for (int i = 0; i < cmds.size(); ++i) {
        std::cout << cmds[i]->to_str() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    /*HivekAssembler::HivekAssembler assembler;

    assembler.open(argv[1]);
    assembler.assemble();
    assembler.write("out.bin");*/
    text_lex();
    test_parser();

    return 0;
}
