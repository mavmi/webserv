#include "../include/utils.hpp"
#include "../include/configurations/parser.hpp"

// не забыть удалить
void runTestConfigFile(int argc, char** argv){
    utilsCheckArgsCount(argc);

    wsrv::Parser parser;
    if (argc == 2){
        parser = wsrv::Parser::parseFile(argv[1]);
    } else {
        parser = wsrv::Parser::parseFile(DEFAULT_SERVER_CONFIG_FILE_PATH);
    }
}

int main(int argc, char** argv){
    std::cout << " == MAIN ONE == " << std::endl;

    (void)argc; (void)argv;
    try {
        runTestConfigFile(argc, argv);
    } catch (wsrv::configuration::Exception& e){
        std::cout << e.what() << std::endl;
    }
}
