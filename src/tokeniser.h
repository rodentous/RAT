#ifndef TOKENISER_H
#define TOKENISER_H

#include "types.h"

int get_priority(std::string text);

Token add_token(std::string text);

std::vector<Token> get_tokens(std::string text);

#endif
