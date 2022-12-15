#include "../include/utils/utils.hpp"
#include "../include/configurations/parser.hpp"

// не забыть удалить
void runTestConfigFile(int argc, char** argv){
    MAIN_NAMESPACE::UTILS_NAMESPACE::utilsCheckArgsCount(argc);

    MAIN_NAMESPACE::Parser parser;
    if (argc == 2){
        parser = MAIN_NAMESPACE::Parser::parseFile(argv[1]);
    } else {
        parser = MAIN_NAMESPACE::Parser::parseFile(MAIN_NAMESPACE::UTILS_NAMESPACE::DEFAULT_SERVER_CONFIG_FILE_PATH);
    }
}

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include <string>
void readFile(){
    std::cout << "\n\t===============================\n" << std::endl;

    const int bufferSize = 16;
    
    int fileFd = open("/home/username/Desktop/httpRequestExample.txt", O_RDONLY);
    if (fileFd == -1){
        std::cerr << "Cannot open file" << std::endl;
        return;
    }

    int lastSize;
    std::vector<char*> content;
    while(true){
        char* buffer = (char*)malloc(bufferSize * sizeof(char));
        int readCount = read(fileFd, buffer, bufferSize);
        content.push_back(buffer);
        if (readCount < bufferSize){
            lastSize = readCount;
            break;
        }
    }
    (void)lastSize;

    // for (size_t i = 0; i < content.size(); i++){
    //     for (int j = 0; j < (i + 1 == content.size() ? lastSize : bufferSize); j++){
    //         std::cout << content[i][j];
    //     }
    // }

    // parseFile(content, bufferSize, lastSize);
    
    for (size_t i = 0; i < content.size(); i++) free(content[i]);
}

int main(int argc, char** argv){
    std::cout << " == MAIN ONE == " << std::endl;

    (void)argc; (void)argv;
    try {
        runTestConfigFile(argc, argv);
    } catch (MAIN_NAMESPACE::UTILS_NAMESPACE::Exception& e){
        std::cout << e.what() << std::endl;
    }

    readFile();
}
