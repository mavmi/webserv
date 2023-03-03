#include "../includes/utils/utils.hpp"
#include "../includes/configurations/parser.hpp"
#include "../includes/core/server.hpp"

// не забыть удалить
const wsrv::Configuration& parseConfig(int argc, char** argv, wsrv::Parser& parser){
    return (argc == 2) ? parser.parseFile(argv[1]) : 
            parser.parseFile(wsrv::utils::DEFAULT_SERVER_CONFIG_FILE_PATH);
}

#include <sys/stat.h>
int main(int argc, char** argv){    
    // struct stat buf;
    // stat(std::string("/Users/pmaryjo/Desktop/1.png").c_str(), &buf);
    // buf.
    // exit(0);


    (void)argc; (void)argv;

    wsrv::utils::utilsCheckArgsCount(argc);
    try {
        wsrv::Parser parser;
        start_server(parseConfig(argc, argv, parser));
    } catch (wsrv::utils::Exception& e){
        std::cout << e.what() << std::endl;
    }
} 
