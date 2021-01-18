#ifndef HIVEK_ASSEMBLER_COMMAND_H
#define HIVEK_ASSEMBLER_COMMAND_H

namespace HivekAssembler {
    typedef enum CommandKind {
        CMD_DIRECTIVE,
        CMD_INSTRUCTION,
        CMD_LABEL
    } CommandKind;

    class Command {
    private:
        CommandKind kind;
    };
}

#endif
