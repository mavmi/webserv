#include "../include/utils.hpp"
#include "../include/configuration.hpp"

#include "../test/test.hpp"

#include <algorithm>
#include <iterator>
#include <assert.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

// не забыть удалить
void runTestConfigFile(int argc, char** argv){
    utilsCheckArgsCount(argc);
    Configuration config;
    config.parseFile(argv[1]);
}

int main(int argc, char** argv){
    (void)argc; (void)argv;

    // RUN_ALL_TESTS();
    runTestConfigFile(argc, argv);
}
