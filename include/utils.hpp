#pragma once

#include <string>
#include <cstdlib>
#include <iostream>
#include <algorithm>

enum MSG_TYPE {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

void        utilsPrintMsg(const std::string& msg, MSG_TYPE msgType);
void        utilsCheckArgsCount(int argc);
int         utilsStringToInt(const std::string& str);
std::string utilsIntToString(int num);
