#include "ratc.h"

#include "preprocessor.h"
#include "types.h"
#include "tokeniser.h"
#include "parser.h"
#include "converter.h"
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
    std::cout << std::endl << "PREPROCESSING:" << std::endl;
    preprocess(&text);

    // DEBUG
    std::cout << text << std::endl;
    // END DEBUG
    
    std::stringstream source(text);
    std::string line;

//////////////////////////////////////////////////////////////////////////////////////
// TOKENISING
//////////////////////////////////////////////////////////////////////////////////////
    std::cout << std::endl << "TOKENISING:" << std::endl;
    std::vector<std::vector<Token>> lines;
    while (std::getline(source, line))
    {
        std::vector<Token> tokens = get_tokens(line);
        lines.push_back(tokens);

        // DEBUG
        for (Token token : tokens)
            std::cout << "<" << token.value << ">";
        std::cout << std::endl;
        // END DEBUG
    }

//////////////////////////////////////////////////////////////////////////////////////
// PARSING
//////////////////////////////////////////////////////////////////////////////////////
    std::cout << std::endl << "PARSING:" << std::endl;
    std::vector<AST> trees;
    for (std::vector<Token> tokens : lines)
    {
        AST tree = *parse(tokens);
        trees.push_back(tree);

        // DEBUG
        print_tree(tree, 0);
        // END DEBUG
    }

//////////////////////////////////////////////////////////////////////////////////////
// CONVERTING
//////////////////////////////////////////////////////////////////////////////////////
    std::cout << std::endl << "CONVERTING:" << std::endl;
    for (AST tree : trees)
    {
        convert(tree);
        std::cout << "data_segment:\n" << CONVERTER_H::data_segment << "\n\ntext_segment:\n" << CONVERTER_H::text_segment << std::endl;
    }
}

std::string usage = R"(
Usage:
    ratc [-o] <output> <input>
    ratc [options] <arguments>
Options:
    -h | --help     print this message
    -o <output>     compiled binary file
    -r || --run     run line of code
)";

int main(int argc, char* argv[])
{
    if (argv[1] == nullptr)
    {
        std::cout << usage << std::endl;
        return 0;
    }
    else if (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")
    {
        std::cout << usage << std::endl;
        return 0;
    }
    else if (std::string(argv[1]) == "-r" || std::string(argv[1]) == "--run")
    {
        compile(argv[2]);
        return 0;
    }
    else
    {
        std::cout << "Unknown option: " << argv[1] << usage << std::endl;
        return 1;
    }
}