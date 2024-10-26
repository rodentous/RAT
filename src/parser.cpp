#include "parser.h"


AST *parse_expression(std::vector<Token> tokens)
{
	if (tokens.empty())
		return nullptr;

	AST *ast = new AST;

	Token highest = tokens.at(0);
	size_t index = 0;
	for (size_t i = 0; i < tokens.size(); i++)
	{
		if (tokens.at(i).priority > highest.priority)
		{
			highest = tokens.at(i);
			index = i;
		}
	}

	ast->value = Token(highest);

	std::vector<Token> left_slice = std::vector<Token>(tokens.begin(), tokens.begin() + index);
	ast->left = parse_expression(left_slice);

	std::vector<Token> right_slice = std::vector<Token>(tokens.begin() + index + 1, tokens.end());
	ast->right = parse_expression(right_slice);

	return ast;
}

std::vector<AST> parse(std::vector<Token> tokens)
{
	std::vector<AST> trees;

	std::vector<Token> buffer;
	for (Token token : tokens)
	{
		if (token.value != ";")
			buffer.push_back(token);
		else
		{
			trees.push_back(*parse_expression(buffer));
			buffer.clear();
		}
	}
	if (!buffer.empty())
		trees.push_back(*parse_expression(buffer));

	return trees;
}
