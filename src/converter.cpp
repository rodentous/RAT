#include "converter.h"
#include <stdexcept>

std::string code;
int highest = 0;

std::string get_var(int num)
{
	return "r" + std::to_string(num);
}

std::string convert(AST tree)
{
	switch (tree.value.type)
	{
	case Token::CONSTANT:
		code += get_var(++highest) + " = " + tree.value.value + "\n";
		break;
	case Token::OPERATOR:
		convert(*tree.left);
		convert(*tree.right);
		code += get_var(highest - 1) + " = " + get_var(highest - 1) + " " + tree.value.value + " " + get_var(highest) +
				"\n";
		highest--;
		break;
	case Token::KEYWORD:
		if (tree.value.value == "write")
		{
			convert(*tree.right);
			code += "write " + get_var(highest) + "\n";
		}
		else if (tree.value.value == "quit")
		{
			convert(*tree.right);
			code += "quit " + get_var(highest) + "\n";
		}
		break;
	default:
		throw std::runtime_error("Unexpected token: " + tree.value.value);
	}
	return code;
}
