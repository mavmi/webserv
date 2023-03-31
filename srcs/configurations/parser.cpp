#include "../../includes/configurations/parser.hpp"

namespace MAIN_NAMESPACE{
ParserException::ParserException(const char* msg) : Exception(msg){}
ParserException::ParserException(const std::string& msg) : Exception(msg){}
ParserException::ParserException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
ParserException::ParserException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
ParserException::ParserException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
ParserException::ParserException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string ParserException::output_() const {
    return "CONFIGURATION_PARSER_EXCEPTION: " + msg_;
}
}


namespace MAIN_NAMESPACE{
Parser::Parser(){}
Parser::Parser(const std::string& inputFile){
    parseFile(inputFile);
}
Parser::Parser(const Parser& other)
    : configuration_(other.configuration_) {

}

Parser& Parser::operator=(const Parser& other){
    configuration_ = other.configuration_;
    return *this;
}

Parser::~Parser(){}

const Configuration& Parser::parseFile(const std::string& inputFile){
    typedef std::string::iterator Iterator;
    typedef CONFIG_NAMESPACE::ServerConfiguration ServerType;
    typedef CONFIG_NAMESPACE::RouteConfiguration RouteType;

    std::ifstream inputFileStream(inputFile.c_str(), std::ios::in);
    if (!inputFileStream.is_open()) throw ExceptionType("Unable to open input file: " + inputFile, EXC_ARGS);

    std::string line;
    while(std::getline(inputFileStream, line)){     // it does not have whitespaces here anymore       
        if (isLineEmpty_(line)) continue;

        Iterator iter = line.begin();
        while (iter != line.end()){
            char c = *iter;

            if (isspace(c));
            else if (c == '{'){          // Start server

                try {
                    ServerType& lastServer = getLastServer_();
                    if (!lastServer.isDone()) throw MAIN_NAMESPACE::UTILS_NAMESPACE::Exception("Unable to start server: the previous one is not done", EXC_ARGS);
                    configuration_.getServers().push_back(ServerType());
                } catch (ExceptionType&){
                    configuration_.getServers().push_back(ServerType());
                } catch (MAIN_NAMESPACE::UTILS_NAMESPACE::Exception&){
                    throw;
                }

            } else if (c == '}'){   // Finish server

                try {
                    ServerType& lastServer = getLastServer_();
                    if (lastServer.isDone()) throw MAIN_NAMESPACE::UTILS_NAMESPACE::Exception("Unable to finish server: it is already finished", EXC_ARGS);
                    if (!getLastRoute_().isDone()) throw MAIN_NAMESPACE::UTILS_NAMESPACE::Exception("Unable to finish server: it contains unfinished route", EXC_ARGS);
                    lastServer.done();
                    configuration_.getHostPortPairs().insert(std::make_pair(lastServer.getHost(), lastServer.getPort()));
                } catch (MAIN_NAMESPACE::CONFIG_NAMESPACE::ServerException&){
                    getLastServer_().done();
                } catch (ExceptionType&){
                    throw;
                } catch (MAIN_NAMESPACE::UTILS_NAMESPACE::Exception&){
                    throw;
                }

            } else if (c == '['){   // Start route for last server

                try {
                    ServerType& lastServer = getLastServer_();
                    if (lastServer.isDone()) throw MAIN_NAMESPACE::UTILS_NAMESPACE::Exception("Unable to start route: there are no unfinished servers to contain one", EXC_ARGS);
                    if (!getLastRoute_().isDone()) throw MAIN_NAMESPACE::UTILS_NAMESPACE::Exception("Unable to start route: there is unfinished one", EXC_ARGS);
                    lastServer.addRoute(RouteType());
                } catch (MAIN_NAMESPACE::CONFIG_NAMESPACE::ServerException&){
                    getLastServer_().addRoute(RouteType());
                } catch (ExceptionType&){
                    throw;
                } catch (MAIN_NAMESPACE::UTILS_NAMESPACE::Exception&){
                    throw;
                }

            } else if (c == ']'){   // Finish route for last server

                try {
                    ServerType& lastServer = getLastServer_();
                    if (lastServer.isDone()) throw MAIN_NAMESPACE::UTILS_NAMESPACE::Exception("Unable to finish route: there are no unfinished servers to contain one", EXC_ARGS);
                    if (getLastRoute_().isDone()) throw MAIN_NAMESPACE::UTILS_NAMESPACE::Exception("Unable to finish route: there are no non-finished routes", EXC_ARGS);
                    getLastRoute_().done();
                } catch (MAIN_NAMESPACE::CONFIG_NAMESPACE::ServerException&){
                    throw;
                } catch (ExceptionType&){
                    throw;
                } catch (MAIN_NAMESPACE::UTILS_NAMESPACE::Exception&){
                    throw;
                }

            } else {                // value string

                const std::string errMsg = "Invalid key-value line";

                Iterator begin = iter;
                Iterator end = std::find(begin, line.end(), ';');
                if (end == line.end()) throw ExceptionType(errMsg, EXC_ARGS);  // Did not find ';' == very bad
                
                std::string substring = line.substr(
                    std::distance(line.begin(), begin),
                    std::distance(begin, end)
                );

                {
                    Iterator iterBegin = std::find(substring.begin(), substring.end(), ':');
                    if (iterBegin == line.end()) throw ExceptionType(errMsg, EXC_ARGS);
                    size_t colonPosNum = std::distance(substring.begin(), iterBegin);
                    Iterator iterEnd = ++iterBegin;
                    while (isspace(*iterEnd)) iterEnd++;
                    if (iterEnd == line.end()) throw ExceptionType(errMsg, EXC_ARGS);
                    substring.erase(iterBegin, iterEnd);

                    while (true){
                        bool exit = false;
                        // Iterator iterBegin = std::next(substring.begin(), colonPosNum);
                        Iterator iterBegin = substring.begin() + colonPosNum;
                        Iterator iterEnd = iterBegin;
                        while (iterEnd != substring.end() && !isspace(*iterEnd)) iterEnd++;
                        if (iterEnd == substring.end()) break;
                        iterBegin = iterEnd;
                        while (iterEnd != substring.end() && isspace(*iterEnd)) iterEnd++;
                        exit = iterEnd == substring.end();
                        substring.erase(iterBegin, iterEnd);
                        if (exit) break;
                    }

                    parseValueString_(substring);
                }

                if (end == line.end()) break;
                iter = ++end;
                continue;

            }

            iter++;
        }
    }

    inputFileStream.close();
    return configuration_;
}
const Configuration& Parser::getConfiguration() const{
    return configuration_;
}

bool Parser::isLineEmpty_(const std::string& line) const{
    if (!line.size()) return true;
    for (size_t i = 0; i < line.size(); i++){
        if (!std::isspace(line[i])) return false;
    }
    return true;
}

CONFIG_NAMESPACE::ServerConfiguration& Parser::getLastServer_(){
    if (!configuration_.getServers().size()) throw ExceptionType("Servers are not defined", EXC_ARGS);
    return configuration_.getServers().back();
}
CONFIG_NAMESPACE::RouteConfiguration& Parser::getLastRoute_() {
    return getLastServer_().getRoutes().back();
}

MAIN_NAMESPACE::UTILS_NAMESPACE::METHOD Parser::stringToHttpMethod_(const std::string& str){
    if (str == "GET") return MAIN_NAMESPACE::UTILS_NAMESPACE::GET;
    else if (str == "POST") return MAIN_NAMESPACE::UTILS_NAMESPACE::POST;
    else if (str == "DELETE") return MAIN_NAMESPACE::UTILS_NAMESPACE::DELETE;
    throw ExceptionType("Invalid HTTP method", EXC_ARGS);
}
std::set<std::string> Parser::stringToArray_(const std::string& str){
    typedef std::string::const_iterator Iterator;
    
    std::set<std::string> result;

    Iterator begin = str.begin();
    Iterator end = str.begin();
    while (end != str.end()) {
        end = std::find(begin, str.end(), ',');
        std::string substring = str.substr(
            std::distance(str.begin(), begin),
            std::distance(begin, end)
        );
        result.insert(substring);
        begin = end + 1;
    }

    return result;
}
bool Parser::stringToBool_(const std::string& str) const {
    if (str == "true") return true;
    else if (str == "false") return false;
    throw ExceptionType("Invalid boolean value", EXC_ARGS);
}

std::pair<std::string, std::string> Parser::split_(const std::string& str) const {
    typedef std::string::const_iterator Iterator;
    const std::string errorMsg = "Invalid key-value line";

    Iterator splitPoint = std::find(str.begin(), str.end(), ':');
    if (splitPoint == str.end()) throw ExceptionType(errorMsg, EXC_ARGS);
    if (std::find(splitPoint + 1, str.end(), ':') != str.end()) throw ExceptionType(errorMsg, EXC_ARGS);

    std::string key = str.substr(0, std::distance(str.begin(), splitPoint));
    std::string value = str.substr(
        std::distance(str.begin(), splitPoint + 1),
        std::distance(splitPoint + 1, str.end())
    );

    return std::make_pair(key, value);
}
void Parser::parseValueString_(const std::string& str){
    typedef CONFIG_NAMESPACE::ServerConfiguration ServerType;

    const std::pair<std::string, std::string> key_value = split_(str);
    const std::string& key = key_value.first;
    const std::string& value = key_value.second;

    // Server configs parsing
    ServerType& lastServer = getLastServer_();
    if (lastServer.isDone()) throw ExceptionType("Trying to update already finished server", EXC_ARGS);
    {
        if (key == "port"){
            lastServer.setPort(stringToNumber_<uint16_t>(value));
            return;
        } else if (key == "host"){
            lastServer.setHost(value);
            return;
        } else if (key == "server_name"){
            lastServer.setServerName(value);
            return;
        } else if (key == "error_pages"){
            std::set<std::string> arr = stringToArray_(value);
            for (std::set<std::string>::const_iterator iter = arr.begin(); iter != arr.end(); iter++){
                lastServer.addErrorPage(*iter);
            }
            return;
        } else if (key == "body_size"){
            lastServer.setBodySize(stringToNumber_<size_t>(value));
            return;
        }
    }
    
    // Route configs parsing
    CONFIG_NAMESPACE::RouteConfiguration& lastRoute = getLastRoute_();
    if (lastRoute.isDone()) throw ExceptionType("Trying to update already finished route", EXC_ARGS);
    {
        if (key == "methods"){
            std::set<std::string> arr = stringToArray_(value);
            for (std::set<std::string>::const_iterator iter = arr.begin(); iter != arr.end(); iter++){
                lastRoute.addMethod(stringToHttpMethod_(*iter));
            }
            return;
        } else if (key == "redir"){
            lastRoute.setRedirection(value);
            return;
        } else if (key == "dir"){
            lastRoute.setDirectory(value);
            return;
        } else if (key == "dir_listening"){
            lastRoute.setDirectoryListening(stringToBool_(value));
            return;
        } else if (key == "def_if_dir"){
            lastRoute.setDefaultIfDirectoryResponse(value);
            return;
        } else if (key == "cgi_script"){
            lastRoute.setCgiScriptPath(value);
            return;
        } else if (key == "cgi_bin"){
            lastRoute.setCgiBinPath(value);
            return;
        } else if (key == "save_files"){
            lastRoute.setSaveFiles(stringToBool_(value));
            return;
        } else if (key == "save_to"){
            lastRoute.setSaveTo(value);
            return;
        }
    }

    // Throw an exception on error
    throw ExceptionType("Invalid key", EXC_ARGS);
}

}
