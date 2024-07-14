#include "types.h"

void Symbol_table::add_variable(std::string &name, Variable &var)
{
	variables[name] = var;
}

Variable Symbol_table::get_variable(std::string &name) 
{
	return variables.at(name);
}

bool Symbol_table::contains(std::string &name)
{
	return variables.find(name) != variables.end();
}
