#include "types.h"
#include "converter.h"
#include <stdexcept>


int highest = 0;
std::vector<Instruction> instructions;
std::map<std::string, int> symbol_table;

void convert_tree(AST tree)
{
	switch (tree.value.type)
	{
	case Token::CONSTANT:
		instructions.push_back(Instruction(Instruction::MOVE, "t-" + std::to_string(++highest), tree.value.value));
		break;

	case Token::VARIABLE:
		if (!symbol_table.contains(tree.value.value))
			error(tree.value, "Undefined variable: ", token_to_string(tree.value));

		instructions.push_back(Instruction(Instruction::MOVE, "t-" + std::to_string(++highest), "v-" + tree.value.value));
	
	case Token::OPERATOR:
		if (tree.value.value == "+")
		{
			if (tree.left == nullptr || tree.right == nullptr)
				error(tree.value, "Invalid expression: ", token_to_string(tree.value));

			convert_tree(*tree.left);
			convert_tree(*tree.right);
				
			instructions.push_back(Instruction(Instruction::ADD, "t-" + std::to_string(--highest), "t-" + std::to_string(highest)));
		}
		else if (tree.value.value == "*")
		{
			if (tree.left == nullptr || tree.right == nullptr)
				error(tree.value, "Invalid expression: ", token_to_string(tree.value));

			convert_tree(*tree.left);
			convert_tree(*tree.right);
				
			instructions.push_back(Instruction(Instruction::MULT, "t-" + std::to_string(--highest), "t-" + std::to_string(highest)));
		}
		else if (tree.value.value == "=")
		{
			if (tree.left == nullptr || tree.right == nullptr)
				error(tree.value, "Invalid expression: ", token_to_string(tree.value));

			convert_tree(*tree.left);
			convert_tree(*tree.right);
			
			if (tree.left->value.type != Token::VARIABLE)
				error(tree.value, "Undefined variable: ", token_to_string(tree.value));

			instructions.push_back(Instruction(Instruction::MOVE, "v-" + tree.left->value.value, "t-" + std::to_string(highest--)));
		}
		break;
	
	case Token::KEYWORD:
		if (tree.value.value == "exit")
		{
			if (tree.right == nullptr)
				error(tree.value, "No exit code provided: ", token_to_string(tree.value));
			
			convert_tree(*tree.right);
			instructions.push_back(Instruction(Instruction::EXIT, "t-" + std::to_string(highest--), ""));
		}
		else if (tree.value.value == "var")
		{
			if (tree.right == nullptr || tree.right->value.type != Token::VARIABLE)
				error(tree.value, "Invalid variable declaration", token_to_string(tree.right->value));
			else if (symbol_table.contains(tree.right->value.value))
				error(tree.value, "Variable redefinition", token_to_string(tree.right->value));

			symbol_table[tree.right->value.value];
			convert_tree(*tree.right);
		}
		break;

	default:
		error(tree.value, "Unexpected token: ", token_to_string(tree.value));
	}
}

std::vector<Instruction> convert(std::vector<AST> trees)
{
	for (AST tree : trees)
		convert_tree(tree);

	return instructions;
}
