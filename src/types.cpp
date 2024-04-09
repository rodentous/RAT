#include "types.h"

template <typename T>
T Variable::get_value() const
{
    T value;
    std::memcpy(&value, data.data(), sizeof(T));
    return value;
}

template <typename T>
void Variable::set_value(const T& value)
{
    data.resize(sizeof(T));
    std::memcpy(data.data(), &value, sizeof(T));
}

void Symbol_table::add_variable(const std::string& name, const Variable& var)
{
    variables[name] = var;
}

Variable Symbol_table::get_variable(const std::string& name) const
{
    return variables.at(name);
}

bool Symbol_table::contains(const std::string& name) const
{
    return variables.find(name) != variables.end();
}