#include "tokeniser.h"

#include "types.h"
#include <map>


std::map<std::string, int> symbol_table;
int symbol_table_index = 0;

int get_number(std::string text)
{
	return std::stoi(text);
}

bool is_number(std::string text)
{
	for (char character : text)
	{
		if (!std::isdigit(character) && !std::isalnum(character) && character != '.' && character != '_')
			return false;
	}
	return std::isdigit(text.at(0));
}

bool is_word(std::string text)
{
	for (char character : text)
	{
		if (!std::isalnum(character) && character != '_')
			return false;
	}
	return std::isalpha(text.at(0));
}

bool is_operator(std::string text)
{
	return operators.contains(text);
}

Token add_token(std::string text)
{
	Token token;
	if (is_word(text))
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
			if (symbol_table.contains(text))
				token.value = symbol_table[text] = symbol_table_index++;
			else
				token.value = symbol_table[text];
			token.priority = 0;
		}
	}
	// Number
	else if (is_number(text))
	{
		token.type = Token::CONSTANT;
		token.value = get_number(text);
		token.priority = 0;
	}
	// Operator
	else if (is_operator(text))
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

		else if (is_word(buffer + character))
			buffer.push_back(character);

		else if (is_number(buffer + character))
			buffer.push_back(character);

		else if (is_operator(buffer + character))
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
