#include "converter.h"
#include <stdexcept>

std::string code;
int highest = 0;

std::string get_var(int num)
{
	return "r" + std::to_string(num);
}

std::string convert(Statement statement)
{
	for (std::variant<AST, Statement> line : statement.lines)
	{
		if (line.index() == 1)
		    convert(std::get<Statement>(line));
		else
			convert_tree(std::get<AST>(line));
	}

	return code;
}

void convert_tree(AST tree)
{
	switch (tree.value.type)
	{
		case Token::CONSTANT:
			code += get_var(++highest) + " = " + tree.value.value + "\n";
			break;
		case Token::OPERATOR:
			convert_tree(*tree.left);
			convert_tree(*tree.right);
			code += get_var(highest - 1) + " = " + get_var(highest - 1) + " " + tree.value.value + " " + get_var(highest) + "\n";
			highest--;
			break;
		case Token::KEYWORD:
			if (tree.value.value == "write")
			{
				convert_tree(*tree.right);
				code += "write " + get_var(highest--) + "\n";
			}
			else if (tree.value.value == "quit")
			{
				convert_tree(*tree.right);
				code += "quit " + get_var(highest--) + "\n";
			}
			break;
		default:
			throw std::runtime_error("Unexpected token: " + tree.value.value);
	}
}