#include "types.h"

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
