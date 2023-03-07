#include "../include/test_utils.hpp"

std::string test_utils::getColor(COLOR color){
    switch (color){
        case YELLOW:
            return "\033[1;33m";
        case CYAN:
            return "\033[0;36m";
        case GREEN:
            return "\033[0;32m";
        default:
            return "\033[0m";
    }
}
bool test_utils::areDoublesEqual(double a, double b){
    const double eps = 1e-6;
    if (std::abs(a - b) < eps) return true;
    return false;
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
