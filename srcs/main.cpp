#include "../includes/utils/utils.hpp"
#include "../includes/configurations/parser.hpp"
#include "../includes/core/server.hpp"

const wsrv::Configuration& parseConfig(int argc, char** argv, wsrv::Parser& parser){
    return (argc == 2) ? parser.parseFile(argv[1]) : 
            parser.parseFile(wsrv::utils::DEFAULT_SERVER_CONFIG_FILE_PATH);
}

int main(int argc, char** argv){    
    std::cout << " << Server is running >> " << std::endl;

    wsrv::utils::utilsCheckArgsCount(argc);
    try {
        wsrv::Parser parser;
        start_server(parseConfig(argc, argv, parser));
    } catch (wsrv::utils::Exception& e){
        std::cout << e.what() << std::endl;
    } catch (wsrv::utils::UtilsException& e){
        std::cout << e.what() << std::endl;
    }
} 
