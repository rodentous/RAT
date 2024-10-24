#include "tokeniser.h"

#include "types.h"
#include <map>
#include <algorithm>


int get_number(std::string text)
{
	for (char character : text)
	{
		character++;
	}
	return 0;
}

Token add_token(std::string text)
{
	Token token;
	if (std::isalpha(text.at(0)) || text.at(0) == '_')
	{
		// Keyword
		if (keywords.contains(text))
		{
			token.type = Token::KEYWORD;
			token.value = keywords[text];
			token.priority = keywords[text];
		}
		// Variable
		else
		{
			token.type = Token::VARIABLE;
			
			std::vector<std::string>::iterator iterator = std::find(symbol_table_entries.begin(), symbol_table_entries.end(), text);
			size_t index = std::distance(symbol_table_entries.begin(), iterator);
			if (index != symbol_table_entries.size())
				token.value = index;
			else
			{
				symbol_table_entries.push_back(text);
				token.value = index;
			}
			token.priority = 0;
		}
	}
	// Constant
	else if (std::isdigit(text.at(0)))
	{
		token.type = Token::CONSTANT;
		token.value = get_number(text);
		token.priority = 0;
	}
	// Operator
	else if (operators.contains(text))
	{
		token.type = Token::OPERATOR;
		token.value = operators[text];
		token.priority = operators[text];
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
