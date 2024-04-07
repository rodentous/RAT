#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include <cstdint>

bool isoperator(char character)
{
    std::vector<char> operators = 
    {
        '+', '-', '*', '/', '=', '!',
    };
    for (char op : operators)
    {
        if (character == op)
            return true;
    }
    return false;
}

struct Token
{
    enum Type
    {
        IDENTIFIER,
        LITERAL,
        OPERATOR,
        // Add more types as needed
    };
    Type type;
    std::string value;

    int line; // Line number where the token appears
    int column; // Column number where the token appears

    Token(Type t, const std::string& v, int l, int c) : type(t), value(v), line(l), column(c) {}
};


struct Variable
{
    enum Type
    {
        INTEGER,
        FLOAT,
        // Add more types as needed
    } type;
    
    std::vector<uint8_t> data; // Raw bytes of variable value

    // Constructor to initialize the type
    Variable(Type t) : type(t) {}

    // Function to set the value of the variable
    template <typename T>
    void setValue(const T& value)
    {
        data.resize(sizeof(T));
        std::memcpy(data.data(), &value, sizeof(T));
    }

    // Function to get the value of the variable
    template <typename T>
    T getValue() const
    {
        T value;
        std::memcpy(&value, data.data(), sizeof(T));
        return value;
    }
};

class SymbolTable
{
private:
    std::map<std::string, Variable> variables;

public:
    void addVariable(const std::string& name, const Variable& var)
    {
        variables[name] = var;
    }

    Variable getVariable(const std::string& name) const
    {
        return variables.at(name);
    }

    bool contains(const std::string& name) const
    {
        return variables.find(name) != variables.end();
    }
};

SymbolTable symbol_table;

Token add_token(std::string text)
{
    Token token;
    if (isalpha(text.at(0)))
    {
        token.value = text;
        if (!symbol_table.contains(text))
            symbol_table.addVariable(text);
    }
    else if (std::isdigit(text.at(0)))
        token.value = text;
    else if (isoperator(text.at(0)))
        token.value = text;
    return token;
}

std::vector<std::vector<Token>> get_tokens(std::string text)
{
    std::vector<std::vector<Token>> lines;
    std::vector<Token> tokens;
    std::string buffer;

    for (char character : text)
    {
        if (buffer.empty())
            buffer.push_back(character);
        else if (std::isalpha(buffer.at(0)) && std::isalnum(character))
            buffer.push_back(character);
        else if (std::isdigit(buffer.at(0)) && std::isalnum(character))
            buffer.push_back(character);
        else if (isoperator(buffer.at(0)) && isoperator(character))
            buffer.push_back(character);
        else if (character != ' ' || character != ';' || character != '\n')
        {
            tokens.push_back(add_token(buffer));
            buffer.clear();
            buffer.push_back(character);
        }
        else if ((character == ';' || character == '\n') && !tokens.empty())
        {
            lines.push_back(tokens);
            tokens.clear();
        }
    }
    if (!buffer.empty())
        tokens.push_back(add_token(buffer));
    return { tokens };
}

std::string compile(std::string source)
{
    std::string output = "";
    for (std::vector<Token> line : get_tokens(source))
    {
        for (Token token : line)
            output += "<" + token.value + "> ";
    }
    return output;
}

int main()
{
    std::cout << compile("rat = cute * 10000;");
}