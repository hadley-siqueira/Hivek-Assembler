#ifndef HIVEK_ASSEMBLER_INSTRUCTION_H
#define HIVEK_ASSEMBLER_INSTRUCTION_H

#include <fstream>
#include <cstdint>

#include "HivekDefs.h"
#include "token/Token.h"
#include "commands/Command.h"

namespace HivekAssembler {
    class Instruction : public Command {
    public:
        Instruction(Token& opcode, Token& ra, Token& rb, Token& rc_or_immd);

    public:
        std::string to_str();

    private:
        Token opcode;
        Token ra;
        Token rb;
        Token rc_or_immd;
    };
}

#endif
