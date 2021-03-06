#ifndef HIVEK_ASSEMBLER_LABEL_H
#define HIVEK_ASSEMBLER_LABEL_H

#include "commands/Command.h"
#include "token/Token.h"

namespace HivekAssembler {
    class Label : public Command {
    public:
        Label(Token& token);

    public:
        std::string to_str();

    private:
        Token token;
    };
}

#endif
