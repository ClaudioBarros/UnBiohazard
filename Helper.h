#pragma once

#include <string>

#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)

std::string getAbsPath(const char* relative_path);

namespace Helper
{

enum Direction {UP, DOWN, LEFT, RIGHT};

}

