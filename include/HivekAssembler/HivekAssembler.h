#ifndef HIVEKASSEMBLER_H
#define HIVEKASSEMBLER_H

#include <cstdint>
#include <map>
#include <vector>

namespace HivekAssembler {
    class HivekAssembler {
    public:
        HivekAssembler();

    public:
        void open(const char* path);
        void assemble();
        void write(const char* path);

    private:
        uint32_t build_ri(int opcode, int ra, int rb, int immd16);
        uint32_t build_rr(int opcode, int ra, int rb, int rc);
        uint32_t build_j(int opcode, int immd26);

    private:
        void build_maps(const std::string &opcode, int kind, int type);
        void build_reg_map();

        bool is_instruction(std::string& v);
        bool is_label(std::string& v);

    private:
        std::map<std::string, int> opcode_map;
        std::map<int, int> opcode_type_map;
        std::map<std::string, int> regs_map;
        std::map<std::string, uint64_t> label_address_map;
        std::vector<std::string> lines;
        std::vector<uint32_t> output;
        uint64_t ip;
    };
}
#endif // HIVEKASSEMBLER_H
