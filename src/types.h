#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <string>
#include <map>
#include <variant>


struct Token
{
	enum Type
	{
		KEYWORD,
		OPERATOR,
		CONSTANT,
		VARIABLE,
	};
	Type type;
	std::string value;
	int priority;

	// where token appears
	int line = 0;
	int column = 0;
};

struct Instruction // assembly instruction
{
	enum Type
	{
		EXIT,
		MOVE,
		ADD,
		SUB,
		MULT,
		PUSH,
	};
	Type type;

	std::string argument1;
	std::string argument2;

	// constructor
	Instruction (Type t, std::string a1, std::string a2) : type(t), argument1(a1), argument2(a2) {}
};

struct AST // Abstract Syntax Tree
{
	Token value;
	AST *left;
	AST *right;
};

struct Statement // block of code
{
	std::vector<std::variant<AST, Statement>> lines;
};


// debug
std::string token_type_to_string(Token::Type type);

std::string instruction_type_to_string(Instruction::Type type);

std::string token_to_string(Token token);

std::string ast_to_string(AST tree, int depth = 0);

std::string instruction_to_string(Instruction instruction);


void error(Token token, std::string error, std::string message = "");


#endif
