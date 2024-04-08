#ifndef TOKENISER_H
#define TOKENISER_H

#include <vector>
#include <string>
#include "types.h"

Token add_token(std::string text);

std::vector<std::vector<Token>> get_tokens(std::string text);

#endif