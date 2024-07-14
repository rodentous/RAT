#include "ratc.h"

#include "converter.h"
#include "parser.h"
#include "preprocessor.h"
#include "tokeniser.h"
#include "types.h"
#include <iostream>

void print_tree(AST root, int depth = 0)
{
	for (int i = 0; i < depth; i++)
		std::cout << "  ";

	std::cout << "<" << root.value.value << ">" << std::endl;
	if (root.left != nullptr)
		print_tree(*root.left, depth + 1);
	if (root.right != nullptr)
		print_tree(*root.right, depth + 1);
}

void print_statement(Statement statement, int depth = 0)
{
	for (std::variant<AST, Statement> stmt : statement.lines)
	{
		if (stmt.index() == 0)
		{
			print_tree(std::get<AST>(stmt), depth);
		}
		else
		{
			std::cout << "{" << std::endl;
			print_statement(std::get<Statement>(stmt), depth + 1);
			std::cout << "}" << std::endl;
		}
	}
}

void compile(std::string source)
{
	std::cout << source << std::endl;
	Symbol_table symbol_table;

//////////////////////////////////////////////////////////////////////////////////////
/// PREPROCESSING
//////////////////////////////////////////////////////////////////////////////////////
	std::cout << "\nPREPROCESSING:" << std::endl;
	preprocess(&source);

	// DEBUG
	std::cout << source << std::endl;
	//

//////////////////////////////////////////////////////////////////////////////////////
// TOKENISING
//////////////////////////////////////////////////////////////////////////////////////
	std::cout << "\nTOKENISING:" << std::endl;

	std::vector<Token> tokens = get_tokens(source);
	// DEBUG
	for (Token token : tokens)
		std::cout << "<" << token.type << ", " << token.value << ">";
	std::cout << std::endl;
	//

//////////////////////////////////////////////////////////////////////////////////////
// PARSING
//////////////////////////////////////////////////////////////////////////////////////
	std::cout << "\nPARSING:" << std::endl;
	Statement code_statement = parse_statement(tokens);

	// DEBUG
	print_statement(code_statement);
	//

//////////////////////////////////////////////////////////////////////////////////////
// CONVERTING
//////////////////////////////////////////////////////////////////////////////////////
	std::cout << "\nCONVERTING:" << std::endl;
	std::string code = convert(code_statement);

	// DEBUG
	std::cout << code;
	//
}

std::string usage = R"(rat compiler
Usage:
    ratc <input> [-o] <output>
    ratc [options] <arguments>
Options:
    -h | --help     print this message
    -o <output>     compiled binary file
    -r |  --run     run code
)";

int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++)
	{
		if (argv[i] == nullptr)
		{
			std::cout << usage << std::endl;
			return 0;
		}
		else if (std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help")
		{
			std::cout << usage << std::endl;
			return 0;
		}
		else if (std::string(argv[i]) == "-r" || std::string(argv[i]) == "--run")
		{
			if (!argv[i + 1])
				return 1;
			compile(argv[i + 1]);
			return 0;
		}
		else
		{
			std::cout << "Unknown option: " << argv[i] << usage << std::endl;
			return 1;
		}
	}
}
