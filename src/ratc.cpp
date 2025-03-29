#include "ratc.h"

#include "types.h"
#include "preprocessor.h"
#include "tokeniser.h"
#include "parser.h"
#include "converter.h"

#include <iostream>
#include <fstream>
#include <filesystem>

std::string compile(std::string source)
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


//////////////////////////////////////////////////////////////////////////////////////
// OUTPUT
//////////////////////////////////////////////////////////////////////////////////////
	std::string output;
	for (Instruction instruction : instructions)
		output += instruction_to_string(instruction);

	return output;
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
	std::ifstream input;
	std::ofstream output;

	for (int i = 1; i < argc; i++)
	{
		if (std::string(argv[i]) == "-h" || std::string(argv[i]) == "--help")
		{
			std::cout << usage << std::endl;
			return 0;
		}
		else if (std::string(argv[i]) == "-r" || std::string(argv[i]) == "--run")
		{
			if (i >= argc - 1)
			{
				std::cout << "Nothing to compile" << std::endl;
				return 1;
			}

			compile(argv[i + 1]);

			return 0;
		}
		else if (std::string(argv[i]) == "-o" || std::string(argv[i]) == "--out")
		{
			if (i == argc - 1 || argv[i + 1][0] == '-')
			{
				std::cout << "No output file" << std::endl;
				return 1;
			}

			output.open(argv[i + 1]);

			if (!output.is_open())
			{
				std::cout << "Wrong output file path" << std::endl;
				return 1;		
			}
		}
		else if (argv[i][0] == '-')
		{
			std::cout << "Unknown option: " << argv[i] << usage << std::endl;
			return 1;
		}
		else
		{
			input.open(argv[i]);

			if (!input.is_open())
			{
				std::cout << "Wrong input file path" << std::endl;
				return 1;
			}
		}
	}

	if (!input.is_open())
	{
		std::cout << "No input file" << std::endl;
		std::cout << usage << std::endl;
		return 1;
	}

	if (!output.is_open())
	{
		std::cout << "Creating default output file" << std::endl;		
		output.clear();
        output.open("output.out", std::ios::out); // create file
        output.close();
        output.open("output.out");
	}

	std::string line;
	std::string source;
	while (std::getline(input, line))
		source += line;
	input.close();

	output << compile(source);
	output.close();

	return 0;
}
