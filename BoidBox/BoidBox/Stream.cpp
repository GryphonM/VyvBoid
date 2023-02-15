#include "Stream.h"

TextStream::TextStream(std::string name)
{
    file.open(name, std::ios::in);
    // if (!file.is_open())
        // Error Message: std::cout << "Failed to open file " << name << " for reading" << std::endl;
}

TextStream::TextStream(const char * name)
{
    file.open(name, std::ios::in);
    // if (!file.is_open())
        // Error Message: std::cout << "Failed to open file " << name << " for reading" << std::endl;
}

TextStream::~TextStream()
{
    if (file.is_open())
        file.close();
}

std::string TextStream::ReadToken()
{
    std::string val;
    file >> val;
    return val;
}

char TextStream::ReadChar()
{
    char val;
    file >> val;
    return val;
}

int TextStream::ReadInt()
{
    int val;
    file >> val;
    return val;
}

bool TextStream::ReadBool(bool isAlpha)
{
    bool val;
    if (isAlpha)
        file >> std::boolalpha >> val;
    else
        file >> val;
    return val;
}
