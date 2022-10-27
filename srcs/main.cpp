#include "../include/utils.hpp"
#include "../include/configurations/configuration.hpp"

// не забыть удалить
void runTestConfigFile(int argc, char** argv){
    utilsCheckArgsCount(argc);
    configuration::Configuration config;
    config.parseFile(argv[1]);
}

int main(int argc, char** argv){
    (void)argc; (void)argv;

    std::cout << " == MAIN ONE == " << std::endl;
    try {
        runTestConfigFile(argc, argv);
    } catch (configuration::Exception& e){
        std::cout << e.what() << std::endl;
    }
}
