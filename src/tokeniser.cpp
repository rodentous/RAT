#include "tokeniser.h"

#include "types.h"
#include <algorithm>

std::vector<std::string> keywords = {
	"quit",
    "write",
};

int get_priority(std::string text)
{
	if (text == "=")
		return 4;
	if (text == "+" || text == "-")
		return 2;
	if (text == "*" || text == "/")
		return 1;
	return 0;
}

Token add_token(std::string text)
{
    Token token;
    token.value = text;
    if (isalpha(text.at(0)))
    {
        if (std::find(keywords.begin(), keywords.end(), token.value) != keywords.end())
       	{
            token.type = Token::KEYWORD;
	        token.priority = 3;
        }
        else
        {
            token.type = Token::VARIABLE;
	        token.priority = 0;
		}
    }
    else if (std::isdigit(text.at(0)))
    {
        token.type = Token::CONSTANT;
        token.priority = 0;
    }
    else if (std::ispunct(text.at(0)))
	{
		token.type = Token::OPERATOR;
		token.priority = get_priority(text);
	}
    return token;
}

std::vector<Token> get_tokens(std::string text)
{
    std::vector<Token> tokens;
    std::string buffer;

    for (char character : text)
    {
        if (buffer.empty())
        {
            if (!std::isspace(character))
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

    return tokens;
}
