#ifndef TYPES_H
#define TYPES_H
#pragma once

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

std::map<int, int> symbol_table;

std::vector<std::string> symbol_table_entries;

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

	int line; // Line number where the token appears
	int column; // Column number where the token appears
};

struct Instruction
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

	Instruction (Type t, int a1, int a2) : type(t), argument1(a1), argument2(a2) {}
};

struct AST
{
	Token value;
	AST *left;
	AST *right;
};

struct Statement
{
	std::vector<std::variant<AST, Statement>> lines;
};


#endif
