#include "ratc.h"

#include "types.h"
#include "tokeniser.h"
#include <iostream>
#include <vector>
#include <string>

std::string compile(std::string source)
{
    SymbolTable symbol_table;

    std::string output = "";
    for (std::vector<Token> tokens : get_tokens(source))
    {
        for (Token token : tokens)
            output += "<" + token.value + ":" + std::to_string(token.type) + "> ";
        output += "\n";
    }
    return output;
}

int main()
{
    std::cout << compile("rat = cute * 10000; lol");
}