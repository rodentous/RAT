#ifndef CONVERTER_H
#define CONVERTER_H

#include "types.h"

std::string get_var(int num);
std::string convert(Statement statement);

void convert_tree(AST tree);

#endif
