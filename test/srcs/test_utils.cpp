#include "../include/test_utils.hpp"

std::string test_utils::getColor(COLOR color){
    switch (color){
        case GREEN:
            return "\033[0;32m";
        default:
            return "\033[0m";
    }
}


TestHeader::TestHeader(const std::string& title){
    std::cout
        << test_utils::getColor(test_utils::GREEN)
        << "==> "
        << title
        << test_utils::getColor(test_utils::DEFAULT)
        << std::endl;
}
TestHeader::~TestHeader(){}
