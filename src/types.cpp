#include "types.h"

#include <iostream>


std::string token_type_to_string(Token::Type type)
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

std::string instruction_type_to_string(Instruction::Type type)
{
	switch(type)
	{
	case Instruction::EXIT:
		return "EXIT";

	case Instruction::MOVE:
		return "MOVE";

	case Instruction::ADD:
		return "ADD";

	case Instruction::SUB:
		return "SUB";

	case Instruction::MULT:
		return "MULT";

	case Instruction::PUSH:
		return "PUSH";

	default:
		return "WRONG-TYPE";
	}
}

std::string token_to_string(Token token)
{
	return "<" + token_type_to_string(token.type) + ": " + token.value + ">";
}

std::string ast_to_string(AST tree, int depth)
{
	std::string result;
	
	for (int i = 0; i < depth; i++)
		result += "  	";

	result += token_to_string(tree.value) + " (priority: " + std::to_string(tree.value.priority) + ")\n";

	if (tree.left != nullptr)
		result += ast_to_string(*tree.left, depth + 1);
	if (tree.right != nullptr)
		result += ast_to_string(*tree.right, depth + 1);

	return result;
}

std::string instruction_to_string(Instruction instruction)
{
	return instruction_type_to_string(instruction.type) + " " + instruction.argument1 + " " + instruction.argument2 + "\n";
}


void error(Token token, std::string error, std::string message)
{
	std::cout << token.line << ":" << token.column << ": " << error << " " << message << std::endl;
	exit(0);
}
