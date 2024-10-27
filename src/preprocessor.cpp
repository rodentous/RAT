#include "preprocessor.h"


void preprocess(std::string *input)
{
	std::string result;
	bool comment;

	for (size_t i = 0; i < input->size(); i++)
	{
		char character = input->at(i);

		if (comment)
		{
			if (character == '\n')
				comment = false;
			else
				continue;
		}

		if (i != input->size() && character == '/' && input->at(i + 1) == '/')
			comment = true;
		
		result += character;
	}
	*input = result;
}
