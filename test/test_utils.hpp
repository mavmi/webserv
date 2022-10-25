#pragma once

#include <string>
#include <iostream>
#include "assert.h"

namespace test_utils{

enum COLOR{
    GREEN,
    DEFAULT
};

std::string getColor(COLOR color){
    switch (color){
        case GREEN:
            return "\033[0;32m";
        default:
            return "\033[0m";
    }
}

}


class TestHeader{
public:
    TestHeader(const std::string& title)
        : prefix_("==> ") {

        std::cout
            << test_utils::getColor(test_utils::GREEN)
            << prefix_
            << title
            << test_utils::getColor(test_utils::DEFAULT)
            << std::endl;
    }
    ~TestHeader(){}

private:
    const std::string prefix_;

};
