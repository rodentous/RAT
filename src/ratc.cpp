#include "ratc.h"

#include "preprocessor.h"
#include "types.h"
#include "tokeniser.h"
#include "parser.h"
#include "converter.h"
#include "code_generator.h"
#include <iostream>
#include <sstream>

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

void compile(std::string text)
{
    std::cout << text << std::endl;
    Symbol_table symbol_table;

//////////////////////////////////////////////////////////////////////////////////////
/// PREPROCESSING
//////////////////////////////////////////////////////////////////////////////////////
    std::cout << "\nPREPROCESSING:" << std::endl;
    preprocess(&text);

    // DEBUG
    std::cout << text << std::endl;
    //
    
    std::stringstream source(text);
    std::string line;

//////////////////////////////////////////////////////////////////////////////////////
// TOKENISING
//////////////////////////////////////////////////////////////////////////////////////
    std::cout << "\nTOKENISING:" << std::endl;
    std::vector<std::vector<Token>> lines;
    while (std::getline(source, line))
    {
        std::vector<Token> tokens = get_tokens(line);
        lines.push_back(tokens);

        // DEBUG
        for (Token token : tokens)
            std::cout << "<" << token.type << ", " << token.value << ">";
        std::cout << std::endl;
        //
    }

//////////////////////////////////////////////////////////////////////////////////////
// PARSING
//////////////////////////////////////////////////////////////////////////////////////
    std::cout << "\nPARSING:" << std::endl;
    std::vector<AST> trees;
    for (std::vector<Token> tokens : lines)
    {
        AST tree = *parse(tokens);
        trees.push_back(tree);

        // DEBUG
        print_tree(tree, 0);
        //
    }

//////////////////////////////////////////////////////////////////////////////////////
// CONVERTING
//////////////////////////////////////////////////////////////////////////////////////
    std::cout << "\nCONVERTING:" << std::endl;
    for (AST tree : trees)
    {
        std::string code = convert(tree);

		// DEBUG
		std::cout << code;
		//
    }

//////////////////////////////////////////////////////////////////////////////////////
// CODE GENERATION
//////////////////////////////////////////////////////////////////////////////////////
    std::cout << "\nGENERATING:" << std::endl;
    
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

int main(int argc, char* argv[])
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
