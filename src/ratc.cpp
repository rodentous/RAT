#include "ratc.h"

#include "types.h"
#include "preprocessor.h"
#include "tokeniser.h"
#include "parser.h"
#include "converter.h"
#include <iostream>
#include <map>

void print_tree(AST root, int depth = 0)
{
	for (int i = 0; i < depth; i++)
		std::cout << "  ";

	std::cout << token_to_string(root.value) << " priority: " << root.value.priority << std::endl;
	if (root.left != nullptr)
		print_tree(*root.left, depth + 1);
	if (root.right != nullptr)
		print_tree(*root.right, depth + 1);
}

void print_instruction(Instruction instruction)
{
	std::cout << instruction.type << " " << instruction.argument1 << " " << instruction.argument2 << std::endl;
}

void compile(std::string source)
{
//////////////////////////////////////////////////////////////////////////////////////
/// PREPROCESSING
//////////////////////////////////////////////////////////////////////////////////////
	preprocess(&source);

	// DEBUG
	std::cout << source << std::endl << std::endl;


//////////////////////////////////////////////////////////////////////////////////////
// TOKENISING
//////////////////////////////////////////////////////////////////////////////////////
	std::vector<Token> tokens = get_tokens(source);

	// DEBUG
	for (Token token : tokens)
		std::cout << token_to_string(token);
	std::cout << std::endl << std::endl;


//////////////////////////////////////////////////////////////////////////////////////
// PARSING
//////////////////////////////////////////////////////////////////////////////////////
	std::vector<AST> trees = parse(tokens);

	// DEBUG
	for (AST tree : trees)
		print_tree(tree);
	std::cout << std::endl;


//////////////////////////////////////////////////////////////////////////////////////
// CONVERTING
//////////////////////////////////////////////////////////////////////////////////////
	std::vector<Instruction> instructions = convert(trees);

	// DEBUG
	for (Instruction instruction : instructions)
		print_instruction(instruction);
}

std::string help = R"(RAT compiler

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
		if (std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help")
		{
			std::cout << help << std::endl;
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
			std::cout << "Unknown option: " << argv[i] << help << std::endl;
			return 1;
		}
	}
	std::cout << help << std::endl;
	return 0;			
}
