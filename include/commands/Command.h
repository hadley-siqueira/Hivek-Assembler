#ifndef HIVEK_ASSEMBLER_COMMAND_H
#define HIVEK_ASSEMBLER_COMMAND_H

#include <string>

namespace HivekAssembler {
    typedef enum CommandKind {
        CMD_DIRECTIVE,
        CMD_INSTRUCTION,
        CMD_LABEL
    } CommandKind;

    class Command {
    public:
        virtual std::string to_str()=0;

    private:
        CommandKind kind;
    };
}

#endif
