#include "types.h"
#include "converter.h"
#include <stdexcept>


int highest = 0;
std::vector<Instruction> instructions;
std::map<int, int> symbol_table;


void convert_tree(AST tree)
{
	switch (tree.value.type)
	{
		case Token::CONSTANT:
			instructions.push_back(Instruction(Instruction::MOVE, ++highest, tree.value.value));
			break;

		case Token::OPERATOR:
			if (tree.value.value == operators["="])
			{
				convert_tree(*tree.left);
				convert_tree(*tree.right);
				if (symbol_table.contains(tree.left->value.value))
					symbol_table[tree.left->value.value] = tree.right->value.value;
				else
					throw std::runtime_error("Undefined variable: "); // + symbol_table_entries[tree.left->value.value]);
			}
			instructions.push_back(Instruction(Instruction::ADD, --highest, tree.value.type));
			break;
		
		case Token::KEYWORD:
			if (tree.value.value == operators["exit"])
			{
				convert_tree(*tree.right);
				instructions.push_back(Instruction(Instruction::EXIT, highest--, tree.right->value.value));
			}
			else if (tree.value.value == operators["var"])
			{
				convert_tree(*tree.right);
				symbol_table[tree.right->value.value];
			}
			break;

		default:
			throw std::runtime_error("Unexpected token: " + '<' + tree.value.type + ' ' + tree.value.value + '>');
	}
}

std::vector<Instruction> convert(std::vector<AST> trees)
{
	for (AST tree : trees)
		convert_tree(tree);

	return instructions;
}
