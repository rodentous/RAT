#include "parser.h"

Statement parse_statement(std::vector<Token> tokens)
{
    Statement statement;
    std::vector<Token> buffer;

    for (size_t i = 0; i < tokens.size(); i++)
    {
        if (tokens.at(i).value == ";")
        {
            if (!buffer.empty())
			{
                statement.lines.push_back(*parse_expression(buffer));
                buffer.clear();
            }
        }
        else if (tokens.at(i).value == "{")
        {
			if (!buffer.empty())
			{
                statement.lines.push_back(*parse_expression(buffer));
                buffer.clear();
            }
            size_t brace_count = 1;
            size_t j = i + 1;
            while (j < tokens.size() && brace_count > 0)
			{
                if (tokens.at(j).value == "{")
                    brace_count++;
                else if (tokens.at(j).value == "}")
                    brace_count--;
                j++;
            }
            if (j < tokens.size())
			{
                statement.lines.push_back(parse_statement(std::vector<Token>(tokens.begin() + i + 1, tokens.begin() + j - 1)));
                i = j - 1;
            }
        }
        else
            buffer.push_back(tokens.at(i));
    }
    if (!buffer.empty())
        statement.lines.push_back(*parse_expression(buffer));

    return statement;
}

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
