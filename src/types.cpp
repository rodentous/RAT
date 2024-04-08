#include "types.h"

#include <vector>
#include <string>
#include <map>
#include <cctype>
#include <cstring>
#include <cstdint>

template <typename T>
T Variable::getValue() const
{
    T value;
    std::memcpy(&value, data.data(), sizeof(T));
    return value;
}

template <typename T>
void Variable::setValue(const T& value)
{
    data.resize(sizeof(T));
    std::memcpy(data.data(), &value, sizeof(T));
}

void SymbolTable::addVariable(const std::string& name, const Variable& var)
{
    variables[name] = var;
}

Variable SymbolTable::getVariable(const std::string& name) const
{
    return variables.at(name);
}

bool SymbolTable::contains(const std::string& name) const
{
    return variables.find(name) != variables.end();
}