#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

bool isoperator(char character)
{
    vector<char> operators = 
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
    string name = "";
    int value = -1;
};

map<string, int> symbol_table;

Token add_token(string text)
{
    Token token;
    if (isalpha(text.at(0)))
    {
        token.name = text;
        if (symbol_table.count(text))
            token.value = symbol_table[text];
        else
        {
            symbol_table[text] = symbol_table.size();
            token.value = symbol_table[text];
        }
    }
    else if (isdigit(text.at(0)))
        token.name = text;
    else if (isoperator(text.at(0)))
        token.name = text;
    return token;
}

vector<vector<Token>> get_tokens(string text)
{
    vector<vector<Token>> lines;
    vector<Token> tokens;
    string buffer;

    for (char character : text)
    {
        if (buffer.empty())
            buffer.push_back(character);
        else if (isalpha(buffer.at(0)) && isalnum(character))
            buffer.push_back(character);
        else if (isdigit(buffer.at(0)) && isalnum(character))
            buffer.push_back(character);
        else if (isoperator(buffer.at(0)) && isoperator(character))
            buffer.push_back(character);
        else if (character != ' ' && character != ';' && character != '\n')
        {
            tokens.push_back(add_token(buffer));
            buffer.clear();
            buffer.push_back(character);
        }
        else if (character == ';' && character == '\n' && !tokens.empty())
        {
            lines.push_back(tokens);
            tokens.clear();
        }
    }
    if (!buffer.empty())
        tokens.push_back(add_token(buffer));
    return {tokens};
}

string compile(string source)
{
    string output = "";
    for (vector<Token> line : get_tokens(source))
    {
        for (Token token : line)
        {
            if (token.value == -1)
                output += "<" + token.name + "> ";
            else
                output += "<" + token.name + ", " + to_string(token.value) + "> ";
        }
    }
    return output;
}

int main()
{
    cout << compile("rat = cute * 10000;");
}