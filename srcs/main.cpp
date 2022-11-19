#include "../include/utils.hpp"
#include "../include/configurations/parser.hpp"

// не забыть удалить
void runTestConfigFile(int argc, char** argv){
    utilsCheckArgsCount(argc);

    Parser parser;
    if (argc == 2){
        parser = Parser::parseFile(argv[1]);
    } else {
        parser = Parser::parseFile(DEFAULT_SERVER_CONFIG_FILE_PATH);
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
