#include "ratc.h"

#include "types.h"
#include "preprocessor.h"
#include "tokeniser.h"
#include "parser.h"
#include "converter.h"

#include <iostream>
#include <filesystem>

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
		std::cout << ast_to_string(tree);
	std::cout << std::endl;


//////////////////////////////////////////////////////////////////////////////////////
// CONVERTING
//////////////////////////////////////////////////////////////////////////////////////
	std::vector<Instruction> instructions = convert(trees);

	// DEBUG
	for (Instruction instruction : instructions)
		std::cout << instruction_to_string(instruction);
}

std::string usage = R"(RAT compiler

Usage:
    ratc [options] <input> [-o] <output>

Options:
    -h | --help           output this message
    -o | --out <path>     path to output binary
    -r | --run <code>     run code
)";

int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++)
	{
		if (std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help")
		{
			std::cout << usage << std::endl;
			return 0;
		}
		else if (std::string(argv[i]) == "-r" || std::string(argv[i]) == "--run")
		{
			if (!argv[i + 1])
			{
				std::cout << "Nothing to compile" << std::endl;
				return 1;
			}
			
			compile(argv[i + 1]);
			
			return 0;
		}
		else if (std::filesystem::exists(argv[i]))
		{

		}
		else
		{
			std::cout << "Unknown option: " << argv[i] << usage << std::endl;
			return 1;
		}
	}
	std::cout << usage << std::endl;
	return 0;
}
