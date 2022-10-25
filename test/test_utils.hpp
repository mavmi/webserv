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
    TestHeader(const std::string& title){

        std::cout
            << test_utils::getColor(test_utils::GREEN)
            << "==> "
            << title
            << test_utils::getColor(test_utils::DEFAULT)
            << std::endl;
    }
    ~TestHeader(){}

};
