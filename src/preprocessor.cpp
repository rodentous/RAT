#include "preprocessor.h"

void preprocess(std::string* input)
{
    std::string result;

    for (char character : *input)
    {
		result += character;
    }
    *input = result;
}
