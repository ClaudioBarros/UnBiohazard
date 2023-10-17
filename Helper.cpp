#include "Helper.h"

#include <string>

std::string getAbsPath(const char* relative_path)
{
    std::string abs_path = STR(PROJECT_DIR);
    return abs_path + relative_path;
}

