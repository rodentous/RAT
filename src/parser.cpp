#include "parser.h"

AST* parse(std::vector<Token> tokens)
{
    if (tokens.empty()) return nullptr;

    AST* ast = new AST;

    Token highest = tokens.at(0);
    size_t index = 0;
    for (int i = 0; i < tokens.size(); i++)
    {
        if (tokens.at(i).type > highest.type)
        {
            highest = tokens.at(i);
            index = i;
        }
    }

    ast->value = Token(highest);
    std::vector<Token> slice;

    slice = std::vector<Token>(tokens.begin(), tokens.begin() + index);
    ast->left = parse(slice);
    
    slice = std::vector<Token>(tokens.begin() + index + 1, tokens.end());
    ast->right = parse(slice);
    
    return ast;
}