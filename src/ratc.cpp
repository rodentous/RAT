#include "ratc.h"

#include "converter.h"
#include "parser.h"
#include "preprocessor.h"
#include "tokeniser.h"
#include "types.h"
#include <iostream>

void print_tree(AST root, int depth)
{
	for (int i = 0; i < depth; i++)
		std::cout << "\t";

	std::cout << "<" << root.value.value << ">" << std::endl;
	if (root.left != nullptr)
		print_tree(*root.left, depth + 1);
	if (root.right != nullptr)
		print_tree(*root.right, depth + 1);
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
	Statement statement = parse_statement(tokens);

	// DEBUG
	for (std::variant<AST, Statement> stmt : statement.lines)
		print_tree(std::get<AST>(stmt), 0);
	//

//////////////////////////////////////////////////////////////////////////////////////
// CONVERTING
//////////////////////////////////////////////////////////////////////////////////////
	std::cout << "\nCONVERTING:" << std::endl;
	for (std::variant<AST, Statement> tree : statement.lines)
	{
		std::string code = convert(std::get<AST>(tree));

		// DEBUG
		std::cout << code;
		//
	}
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
