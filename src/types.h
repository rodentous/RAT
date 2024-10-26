#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <vector>
#include <variant>
#include <map>


std::map<std::string, int> keywords {
	{"exit" , 0},
	{"write", 1}
};

std::map<std::string, int> operators {
	{"=" , 0},
	{"==", 1},
	{">=", 2},
	{"<=", 3},
	{"+" , 4},
	{"-" , 5},
	{"*" , 6},
	{"/" , 7},
};

struct Token
{
	enum Type
	{
		KEYWORD,
		OPERATOR,
		CONSTANT,
		VARIABLE,
		ENDLINE,
	};
	Type type;
	int value;
	int priority;

	// where token appears
	int line;
	int column;
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
		POP,
	};
	Type type;

	int argument1;
	int argument2;

	// constructor
	Instruction (Type t, int a1, int a2) : type(t), argument1(a1), argument2(a2) {}
};

struct AST // Abstract Syntax Tree
{
	Token value;
	AST *left;
	AST *right;
};

struct Statement // block of syntax trees
{
	std::vector<std::variant<AST, Statement>> lines;
};


#endif
