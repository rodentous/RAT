#ifndef CONVERTER_H
#define CONVERTER_H

#include "types.h"

extern std::string code;
extern int highest;

std::string get_var(int num);
void convert(AST trees);

#endif
