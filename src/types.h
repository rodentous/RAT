#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <string>
#include <map>
#include <cstdint>
#include <cctype>
#include <cstring>

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

    int line; // Line number where the token appears
    int column; // Column number where the token appears

    // Constructor
    Token(Type t, const std::string& v, int l, int c) : type(t), value(v), line(l), column(c) {}

    Token() : type(CONSTANT), value(""), line(0), column(0) {} // Default constructor
};

struct AST
{
    Token value;
    AST* left;
    AST* right;
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
    
    std::vector<uint8_t> data; // Raw bytes of variable value

    // Constructor
    Variable(Type t) : type(t) {}

    Variable() : type(NONE) {} // Default constructor

    // Function to set the value of the variable
    template <typename T>
    void set_value(const T& value);

    // Function to get the value of the variable
    template <typename T>
    T get_value() const;
};

class Symbol_table
{
private:
    std::map<std::string, Variable> variables;

public:
    void add_variable(const std::string& name, const Variable& var);
    Variable get_variable(const std::string& name) const;
    bool contains(const std::string& name) const;
};

#endif