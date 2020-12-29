#include <iostream>

#include "HivekAssembler/HivekAssembler.h"

int main(int argc, char* argv[]) {
    HivekAssembler::HivekAssembler assembler;

    assembler.open(argv[1]);
    assembler.assemble();
    assembler.write("out.bin");

    return 0;
}
