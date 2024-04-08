#include "tokeniser.h"

#include "types.h"
#include <vector>
#include <string>

Token add_token(std::string text)
{
    Token token;
    token.value = text;
    if (isalpha(text.at(0)))
        token.type = Token::VARIABLE;
    else if (std::isdigit(text.at(0)))
        token.type = Token::CONSTANT;
    else if (std::ispunct(text.at(0)))
        token.type = Token::OPERATOR;
    return token;
}

std::vector<std::vector<Token>> get_tokens(std::string text)
{
    std::vector<std::vector<Token>> lines;
    std::vector<Token> tokens;
    std::string buffer;

    for (char character : text)
    {
        if (character == ';' || character == '\n')
        {
            if (!buffer.empty())
                tokens.push_back(add_token(buffer));
            buffer.clear();
            lines.push_back(tokens);
            tokens.clear();
        }
        
        else if (buffer.empty())
        {
            if (!isspace(character))
                buffer.push_back(character);
        }
        else if (std::isalpha(buffer.at(0)) && std::isalnum(character))
            buffer.push_back(character);
        else if (std::isdigit(buffer.at(0)) && std::isalnum(character))
            buffer.push_back(character);
        else if (std::ispunct(buffer.at(0)) && std::ispunct(character))
            buffer.push_back(character);
        else
        {
            tokens.push_back(add_token(buffer));
            buffer.clear();
            
            if (!std::isspace(character))
                buffer.push_back(character);
        }
    }
    if (!buffer.empty())
        tokens.push_back(add_token(buffer));

    if (!tokens.empty())
        lines.push_back(tokens);
    return lines;
}