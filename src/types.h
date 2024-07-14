#ifndef TYPES_H
#define TYPES_H

#include <cctype>
#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include <variant>

struct Token
{
	enum Type
	{
		CONSTANT,
		VARIABLE,
		OPERATOR,
		KEYWORD,
 // ...
	};
	Type type;
	std::string value;
	int priority;

	int line; // Line number where the token appears
	int column; // Column number where the token appears
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

struct Variable
{
	enum Type
	{
		NONE,
		INTEGER,
		FLOAT,
 // ...
	} type;

	std::vector<uint8_t> data; // Raw bytes of data
};

class Symbol_table
{
  private:
	std::map<std::string, Variable> variables;

  public:
	void add_variable(std::string &name, Variable &var);
	Variable get_variable(std::string &name);
	bool contains(std::string &name);
};

#endif
