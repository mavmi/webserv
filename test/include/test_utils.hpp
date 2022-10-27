#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "unistd.h"
#include "assert.h"
#include <sys/wait.h>
#include <sys/types.h>

namespace test_utils{

enum COLOR{
    GREEN,
    DEFAULT
};

std::string getColor(COLOR color);

}

class TestHeader{
public:
    TestHeader(const std::string& title);
    ~TestHeader();

};
