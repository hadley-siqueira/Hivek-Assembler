#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>

#include "HivekAssembler/HivekAssembler.h"
#include "HivekDefs.h"

using namespace HivekAssembler;

HivekAssembler::HivekAssembler::HivekAssembler() {
    ip = 0;

    build_maps("add", OPCODE_ADD, TYPE_RR);
    build_maps("sub", OPCODE_SUB, TYPE_RR);
    build_maps("and", OPCODE_AND, TYPE_RR);
    build_maps("or", OPCODE_OR, TYPE_RR);
    build_maps("xor", OPCODE_XOR, TYPE_RR);

    build_maps("addi", OPCODE_ADDI, TYPE_RI);

    build_maps("ld", OPCODE_LOAD_D, TYPE_RI);
    build_maps("sd", OPCODE_STORE_D, TYPE_RI);
    build_maps("beq", OPCODE_BEQ, TYPE_RI);
    build_maps("bne", OPCODE_BNE, TYPE_RI);
    build_maps("blt", OPCODE_BLT, TYPE_RI);

    build_maps("jal", OPCODE_JAL, TYPE_J);
    build_maps("jr", OPCODE_JR, TYPE_RR);

    build_maps("syscall", OPCODE_SYSCALL, TYPE_RR);
    build_maps("halt", OPCODE_HALT, TYPE_RR);

    build_reg_map();
}

void HivekAssembler::HivekAssembler::open(const char *path) {
    std::ifstream file;
    std::string tmp;

    file.open(path);

    while (file.good()) {
        std::getline(file, tmp);
        lines.push_back(tmp);
    }
}

void HivekAssembler::HivekAssembler::assemble() {
    // first pass
    for (int i = 0; i < lines.size(); ++i) {
        std::stringstream s(lines[i]);
        std::string tmp;

        s >> tmp;

        if (is_label(tmp)) {
            tmp.pop_back();
            label_address_map[tmp] = ip;
        } else if (is_instruction(tmp)) {
            ip += 4;
        }
    }

    ip = 0;

    // second pass
    for (int i = 0; i < lines.size(); ++i) {
        std::stringstream s(lines[i]);
        std::string tmp;

        s >> tmp;

        if (is_instruction(tmp)) {
            int opcode  = opcode_map[tmp];
            int ra = 0;
            int rb = 0;
            int rc = 0;
            int immd16 = 0;
            int immd26 = 0;
            uint32_t inst;

            if (opcode_type_map[opcode] == TYPE_RI) {
                s >> tmp;
                rb = regs_map[tmp];

                s >> tmp;
                ra = regs_map[tmp];

                s >> tmp;

                if (label_address_map.count(tmp) > 0) {
                    immd16 = (label_address_map[tmp] - ip) / 4;
                } else {
                    std::stringstream t(tmp);
                    t >> immd16 ;
                }

                inst = build_ri(opcode, ra, rb, immd16);
                output.push_back(inst);
                printf("imap[0x%08x] = \"%s\";\n", inst, lines[i].c_str());
            } else if (opcode_type_map[opcode] == TYPE_RR) {
                if (opcode == OPCODE_SYSCALL || opcode == OPCODE_HALT || opcode == OPCODE_JR) {

                } else {
                    s >> tmp;
                    rc = regs_map[tmp];

                    s >> tmp;
                    ra = regs_map[tmp];

                    s >> tmp;
                    rb = regs_map[tmp];
                }

                inst = build_rr(opcode, ra, rb, rc);
                output.push_back(inst);
                printf("imap[0x%08x] = \"%s\";\n", inst, lines[i].c_str());
            } else if (opcode_type_map[opcode] == TYPE_J) {
                s >> tmp;

                if (label_address_map.count(tmp) > 0) {
                    immd26 = (label_address_map[tmp] - ip) / 4;
                } else {
                    std::stringstream t(tmp);
                    t >> immd26 ;
                }

                inst = build_j(opcode, immd26);
                output.push_back(inst);
                printf("imap[0x%08x] = \"%s\";\n", inst, lines[i].c_str());
            }

            ip += 4;
        }
    }
}

void HivekAssembler::HivekAssembler::write(const char *path) {
    std::ofstream file;
    uint32_t data;

    file.open(path, std::ios::binary);

    for (int i = 0; i < output.size(); ++i) {
        data = output[i];

        file.put((data >> 24) & 0x0ff);
        file.put((data >> 16) & 0x0ff);
        file.put((data >>  8) & 0x0ff);
        file.put((data >>  0) & 0x0ff);
    }

    file.close();
}

uint32_t HivekAssembler::HivekAssembler::build_ri(int opcode, int ra, int rb, int immd16) {
    uint32_t res = 0;

    res = opcode;
    res = (res << 5) | (ra & 0x1f);
    res = (res << 5) | (rb & 0x1f);
    res = (res << 16) | (immd16 & 0x0ffff);

    return res;
}

uint32_t HivekAssembler::HivekAssembler::build_rr(int opcode, int ra, int rb, int rc) {
    uint32_t res = 0;

    res = (res << 5) | (ra & 0x1f);
    res = (res << 5) | (rb & 0x1f);
    res = (res << 5) | (rc & 0x1f);
    res = (res << 11) | (opcode & 0x07ff);

    return res;
}

uint32_t HivekAssembler::HivekAssembler::build_j(int opcode, int immd26) {
    uint32_t res = 0;

    res = opcode;
    res = (res << 26) | immd26 & 0x3ffffff;

    return res;
}

void HivekAssembler::HivekAssembler::build_maps(const std::string &opcode, int kind, int type) {
    opcode_map[opcode] = kind;
    opcode_type_map[kind] = type;
}

void HivekAssembler::HivekAssembler::build_reg_map() {
    for (int i = 0; i < N_REGISTERS; ++i) {
        std::stringstream s;
        s << "%" << i;
        regs_map[s.str()] = i;
        s << ',';
        regs_map[s.str()] = i;
    }

    regs_map["sp"] = REG_SP;
    regs_map["sp,"] = REG_SP;

    regs_map["a0"] = REG_A0;
    regs_map["a0,"] = REG_A0;

    regs_map["a1"] = REG_A1;
    regs_map["a1,"] = REG_A1;

    regs_map["v0"] = REG_V0;
    regs_map["v0,"] = REG_V0;

    regs_map["v1"] = REG_V1;
    regs_map["v1,"] = REG_V1;

    regs_map["t0"] = REG_T0;
    regs_map["t0,"] = REG_T0;

    regs_map["ra"] = REG_RA;
    regs_map["ra,"] = REG_RA;
}

bool HivekAssembler::HivekAssembler::is_instruction(std::string& v) {
    return opcode_map.count(v) > 0;
}

bool HivekAssembler::HivekAssembler::is_label(std::string &v) {
    return v[v.size() - 1] == ':';
}
