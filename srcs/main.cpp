#include "../include/utils/utils.hpp"
#include "../include/configurations/parser.hpp"

// не забыть удалить
void runTestConfigFile(int argc, char** argv){
    MAIN_NAMESPACE::UTILS_NAMESPACE::utilsCheckArgsCount(argc);

    MAIN_NAMESPACE::Parser parser;
    if (argc == 2){
        parser.parseFile(argv[1]);
    } else {
        parser.parseFile(MAIN_NAMESPACE::UTILS_NAMESPACE::DEFAULT_SERVER_CONFIG_FILE_PATH);
    }
}

int main(int argc, char** argv){
    std::cout << " == MAIN ONE == " << std::endl;

    (void)argc; (void)argv;
    try {
        runTestConfigFile(argc, argv);
    } catch (MAIN_NAMESPACE::UTILS_NAMESPACE::Exception& e){
        std::cout << e.what() << std::endl;
    }
}
