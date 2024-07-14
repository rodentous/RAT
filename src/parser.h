#ifndef PARSER_H
#define PARSER_H

#include "types.h"

Statement parse_statement(std::vector<Token> tokens);
AST *parse_expression(std::vector<Token> tokens);

#endif