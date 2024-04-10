#include "converter.h"
#include <stdexcept>

std::string data_segment;
std::string text_segment;

void convert(AST tree)
{
    switch (tree.value.type)
    {
        case Token::CONSTANT:
            text_segment += "take " + tree.value.value + "\n";
            break;
        case Token::OPERATOR:
            convert(*tree.left);
            convert(*tree.right);
            text_segment += "take result of " + tree.value.value + "\n";
            break;
        case Token::KEYWORD:
            if (tree.value.value == "var")
                data_segment += "reserve 4 bites for " + tree.value.value + "\n";
            else if (tree.value.value == "write")
                text_segment += "write\n";
            break;
        case Token::VARIABLE:
            text_segment += "take " + tree.value.value + "\n";
            break;
        default:
            throw std::runtime_error("Unexpected token: " + tree.value.value);
    }
}