#ifndef TYPES_H
#define TYPES_H

#include <map>
#include <vector>
#include <string>
#include <cstdint>

struct Token
{
    enum Type
    {
        VARIABLE,
        CONSTANT,
        OPERATOR,
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


struct Variable
{
    enum Type
    {
    	NONE,
        INTEGER,
        FLOAT,
        // Add more types as needed
    } type;
    
    std::vector<uint8_t> data; // Raw bytes of variable value

    // Constructor
    Variable(Type t) : type(t) {}

    Variable() : type(NONE) {} // Default constructor

    // Function to set the value of the variable
    template <typename T>
    void setValue(const T& value);

    // Function to get the value of the variable
    template <typename T>
    T getValue() const;
};

class SymbolTable
{
private:
    std::map<std::string, Variable> variables;

public:
    void addVariable(const std::string& name, const Variable& var);
    Variable getVariable(const std::string& name) const;
    bool contains(const std::string& name) const;
};

#endif