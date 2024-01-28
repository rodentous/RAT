#include <string>
#include <vector>

using namespace std;

bool isoperator(char character)
{
    vector<char> operators = 
    {
        '+', '-', '*', '/', '=', '!',
    };
    for (char operator : operators)
    {
        if (character == operator)
            return true;
    }
    return false;
}

struct Token
{
    string name;
    int value;
}

map<string, int> symbol_table;

Token add_token(string text)
{
    Token token;
    if (isalpha(text.at(0)))
    {
        token.name = "id";
        if (symbol_table.contains("text"))
            token.value = symbol_table[text];
        else
        {
            symbol_table[text] = symbol_table.size();
            token.value = symbol_table[text];
        }
    }
    else if (isdigit(text.at(0)))
    {
        token.name = "number";
        token.value = text;
    }
    else if (isoperator(text.at(0)))
    {
        token.name = "operator";
        token.value = text;
    }
    return token;
}

vector<vector<Token>> get_tokens(string text)
{
    vector<vector<Token>> lines;
    vector<Token> tokens;
    vector<char> buffer;

    for (char character : source)
    {
        if (buffer.empty())
            buffer.push_back(character);
        else if (isalpha(buffer.at(0)) && isalnum(character))
            buffer.push_back(character);
        else if (isdigit(buffer.at(0)) && isalnum(character))
            buffer.push_back(character);
        else if (isoperator(buffer.at(0)) && isoperator(character))
            buffer.push_back(character);
        else if (character != ' ' && character != ';' && character != "\n")
        {
            tokens.push_back(add_token(buffer));
            buffer.clear();
            buffer.push_back(character);
        }
        else if (character == ';' && character == "\n")
        {
            lines.push_back(tokens);
            tokens.clear();
        }
    }
    return lines;
}

string compile(string source)
{
    get_tokens(source);
    string output = "";
    for (vector<Token> line : get_tokens(source))
    {
        for (Token token : line)
            output += "<" + token.name + ", " + token.value + "> "
    }
    return output;
}