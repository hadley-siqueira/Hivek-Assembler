#include "instructions/Instruction.h"

using namespace HivekAssembler;

Instruction::Instruction(Opcode opcode, int rc, int ra, int rb) {
    this->opcode = opcode;
    this->rc = rc;
    this->ra = ra;
    this->rb = rb;
}
        
void Instruction::write(std::ofstream& file) {
    switch (opcode) {
    // alu
    case OPCODE_32_ADDI:
    case OPCODE_32_ANDI:
    case OPCODE_32_ORI:
    case OPCODE_32_XORI:
        generate32(file);
        break;

    // memory
    case OPCODE_32_LD:
    case OPCODE_32_SD:
        generate32(file);
        break;

    // branches
    case OPCODE_32_BEQ:
    case OPCODE_32_BNE:
    case OPCODE_32_BLT:
        generate32(file);
        break;
    }
}
        
void Instruction::generate32(std::ofstream& file) {
    uint32_t result = 0xe0000000;

    result = 0x7;
    result = (result << 6) | opcode;
    result = (result << 5) | ra;
    result = (result << 5) | rb;
    result = (result << 13) | immd;

    file.put((result >> 24) & 0x0ff);
    file.put((result >> 16) & 0x0ff);
    file.put((result >> 8)  & 0x0ff);
    file.put((result >> 0)  & 0x0ff);
}
