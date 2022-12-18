#pragma once

#include <string>
#include <vector>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <algorithm>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "unistd.h"
#include "assert.h"

namespace test_utils{

enum COLOR{
    YELLOW,
    CYAN,
    GREEN,
    DEFAULT
};

std::string getColor(COLOR color);
bool areDoublesEqual(double a, double b);

}

class TestHeader{
public:
    TestHeader(const std::string& title);
    ~TestHeader();

};
