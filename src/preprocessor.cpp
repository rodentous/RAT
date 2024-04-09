#include "preprocessor.h"

void preprocess(std::string* input)
{
    return;
    std::string result;

    // somehow make defines
    //
    //
    //

    // cringe way to delete comments
    char commented;
    for (char character : result)
    {
        if (commented)
        {
            if (character == commented)
                commented = 0;
            if (character != '\n')
                continue;
        }
        
        else if (character == ';')
            character = '\n';
        else if (character == '#')
        {
            commented = '\n';
            continue;
        }
        else if (character == '[')
        {
            commented = ']';
            continue;
        }
        result += character;
    }
    *input = result;
}