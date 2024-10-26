#include "types.h"


std::string type_to_string(Token::Type type)
{
	switch(type)
	{
		case Token::VARIABLE:
			return "VARIABLE";
		
		case Token::KEYWORD:
			return "KEYWORD";
		
		case Token::OPERATOR:
			return "OPERATOR";
			
		case Token::CONSTANT:
			return "CONSTANT";

		default:
			return "WRONG-TYPE";
	}
}

std::string token_to_string(Token token)
{
	return "<" + type_to_string(token.type) + ": " + token.value + ">";
}

void error(Token token, std::string error, std::string message = "")
{
	std::cout << token.line << ":" << token.column << ": " << error << " " << message << std::endl;
	exit(0);
}
