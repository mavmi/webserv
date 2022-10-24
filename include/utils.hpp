#pragma once

#include <string>
#include <cstdlib>
#include <iostream>

enum MSG_TYPE {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

void utilsPrintMsg(const std::string& msg, MSG_TYPE msgType);
void utilsCheckArgsCount(int argc);
