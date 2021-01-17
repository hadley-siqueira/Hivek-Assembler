#ifndef HIVEK_ASSEMBLER_INSTRUCTION_H
#define HIVEK_ASSEMBLER_INSTRUCTION_H

#include <fstream>
#include <cstdint>

#include "HivekDefs.h"

namespace HivekAssembler {
    class Instruction {
    public:
        Instruction(Opcode opcode, int reg_dst, int reg_src1, int reg_src2);

    public:
        void write(std::ofstream& file);

    private:
        void generate32(std::ofstream &file);

    private:
        Opcode opcode;
        int ra;
        int rb;
        int rc;
        int immd;
        std::string s_immd;
    };
}

#endif
