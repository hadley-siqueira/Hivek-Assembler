#include "commands/label/Label.h"

using namespace HivekAssembler;


Label::Label(Token &token) {
    this->token = token;
}

std::string Label::to_str() {
    return token.getLexem() + ":";
}
