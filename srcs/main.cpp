#include "../include/utils.hpp"
#include "../include/configurations/configuration.hpp"

// не забыть удалить
void runTestConfigFile(int argc, char** argv){
    utilsCheckArgsCount(argc);
    configuration::Configuration config;

    if (argc == 2){
        config.parseFile(argv[1]);
    } else {
        config.parseFile(DEFAULT_SERVER_CONFIG_FILE_PATH);
    }
}

int main(int argc, char** argv){
    std::cout << " == MAIN ONE == " << std::endl;

    (void)argc; (void)argv;
    try {
        runTestConfigFile(argc, argv);
    } catch (configuration::Exception& e){
        std::cout << e.what() << std::endl;
    }
}
