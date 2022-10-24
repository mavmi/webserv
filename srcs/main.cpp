#include "../include/utils.hpp"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

int main(int argc, char** argv){
    (void)argv;

    utilsCheckArgsCount(argc);
    
    std::stringstream stream;
    std::ifstream fileStream(std::string("ConfigFileExample.txt").c_str(), std::ios::in);

    std::string line;
    std::string content;
    while (fileStream >> line){
        content += line;
    }

    std::cout << content << std::endl;
}
