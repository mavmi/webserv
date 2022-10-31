#include "../../include/configurations/configuration.hpp"

namespace configuration {

Configuration::Configuration(){
    servers_ = new ServersContainerType();
}
Configuration::Configuration(const Configuration& other){
    copyData_(other);
}
Configuration::~Configuration(){
    deleteData_();
}

Configuration& Configuration::operator=(const Configuration& other){
    deleteData_();
    copyData_(other);
    return *this;
}
Configuration::ServersContainerType& Configuration::getServers(){
    return *servers_;
}

void Configuration::parseFile(const std::string& inputFile){
    typedef std::string::iterator Iterator;

    std::ifstream inputFileStream(inputFile.c_str(), std::ios::in);
    if (!inputFileStream.is_open()) throw ExceptionType("Unable to open input file: " + inputFile, __FILE__, __FUNCTION__, __LINE__);

    std::string line;
    while(std::getline(inputFileStream, line)){     // it does not have whitespaces here anymore    
        if (isLineEmpty_(line)) continue;
        line.resize(std::distance(line.begin(), std::remove_if(line.begin(), line.end(), isspace)));    // Remove whitespaces from line

        Iterator iter = line.begin();
        while (iter != line.end()){
            char c = *iter;

            if (c == '{'){          // Start server

                try {
                    ServerType& lastServer = getLastServer_();
                    if (!lastServer.isDone()) throw Exception("Unable to start server: the previous one is not done", __FILE__, __FUNCTION__, __LINE__);
                    servers_->push_back(ServerType());
                } catch (ExceptionType&){
                    servers_->push_back(ServerType());
                } catch (Exception&){
                    throw;
                }

            } else if (c == '}'){   // Finish server

                try {
                    ServerType& lastServer = getLastServer_();
                    if (lastServer.isDone()) throw Exception("Unable to finish server: it is already finished", __FILE__, __FUNCTION__, __LINE__);
                    if (!getLastRoute_().isDone()) throw Exception("Unable to finish server: it contains unfinished route", __FILE__, __FUNCTION__, __LINE__);
                    lastServer.done();
                } catch (ServerException&){
                    getLastServer_().done();
                } catch (ExceptionType&){
                    throw;
                } catch (Exception&){
                    throw;
                }

            } else if (c == '['){   // Start route for last server

                try {
                    ServerType& lastServer = getLastServer_();
                    if (lastServer.isDone()) throw Exception("Unable to start route: there are no unfinished servers to contain one", __FILE__, __FUNCTION__, __LINE__);
                    if (!getLastRoute_().isDone()) throw Exception("Unable to start route: there is unfinished one", __FILE__, __FUNCTION__, __LINE__);
                    lastServer.addRoute(ServerType::RouteType());
                } catch (ServerException&){
                    getLastServer_().addRoute(ServerType::RouteType());
                } catch (ExceptionType&){
                    throw;
                } catch (Exception&){
                    throw;
                }

            } else if (c == ']'){   // Finish route for last server

                try {
                    ServerType& lastServer = getLastServer_();
                    if (lastServer.isDone()) throw Exception("Unable to finish route: there are no unfinished servers to contain one", __FILE__, __FUNCTION__, __LINE__);
                    if (getLastRoute_().isDone()) throw Exception("Unable to finish route: there are no non-finished routes", __FILE__, __FUNCTION__, __LINE__);
                    getLastRoute_().done();
                } catch (ServerException&){
                    throw;
                } catch (ExceptionType&){
                    throw;
                } catch (Exception&){
                    throw;
                }

            } else {                // value string

                Iterator begin = iter;
                Iterator end = std::find(begin, line.end(), ';');
                if (end == line.end()) throw ExceptionType("Invalid key-value line", __FILE__, __FUNCTION__, __LINE__);  // Did not find ';' == very bad
                
                std::string substring = line.substr(
                    std::distance(line.begin(), begin),
                    std::distance(begin, end)
                );

                parseValueString_(substring);

                if (end == line.end()) break;
                iter = ++end;
                continue;

            }

            iter++;
        }
    }

    inputFileStream.close();
}

bool Configuration::isLineEmpty_(const std::string& line) const{
    if (!line.size()) return true;
    for (size_t i = 0; i < line.size(); i++){
        if (!std::isspace(line[i])) return false;
    }
    return true;
}

Configuration::ServerType& Configuration::getLastServer_(){
    if (!servers_->size()) throw ExceptionType("Servers are not defined", __FILE__, __FUNCTION__, __LINE__);
    return servers_->back();
}
Configuration::ServerType::RouteType& Configuration::getLastRoute_(){
    return getLastServer_().getRoutes().back();
}

HTTP_METHOD Configuration::stringToHttpMethod_(const std::string& str){
    if (str == "GET") return GET;
    else if (str == "POST") return POST;
    else if (str == "DELETE") return DELETE;
    throw ExceptionType("Invalid HTTP method", __FILE__, __FUNCTION__, __LINE__);
}
std::set<std::string> Configuration::stringToArray_(const std::string& str){
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
bool Configuration::stringToBool_(const std::string& str) const {
    if (str == "true") return true;
    else if (str == "false") return false;
    throw ExceptionType("Invalid boolean value", __FILE__, __FUNCTION__, __LINE__);
}

std::pair<std::string, std::string> Configuration::split_(const std::string& str) const {
    typedef std::string::const_iterator Iterator;
    const std::string errorMsg = "Invalid key-value line";

    Iterator splitPoint = std::find(str.begin(), str.end(), ':');
    if (splitPoint == str.end()) throw ExceptionType(errorMsg, __FILE__, __FUNCTION__, __LINE__);
    if (std::find(splitPoint + 1, str.end(), ':') != str.end()) throw ExceptionType(errorMsg, __FILE__, __FUNCTION__, __LINE__);

    std::string key = str.substr(0, std::distance(str.begin(), splitPoint));
    std::string value = str.substr(
        std::distance(str.begin(), splitPoint + 1),
        std::distance(splitPoint + 1, str.end())
    );

    return std::make_pair(key, value);
}
void Configuration::parseValueString_(const std::string& str){
    const std::pair<std::string, std::string> key_value = split_(str);
    const std::string& key = key_value.first;
    const std::string& value = key_value.second;

    // Server configs parsing
    ServerType& lastServer = getLastServer_();
    if (lastServer.isDone()) throw ExceptionType("Trying to update already finished server", __FILE__, __FUNCTION__, __LINE__);
    {
        if (key == "port"){
            lastServer.setPort(stringToNumber_<ServerType::PortType>(value));
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
            lastServer.setBodySize(stringToNumber_<ServerType::BodySizeType>(value));
            return;
        }
    }
    
    // Route configs parsing
    ServerType::RouteType& lastRoute = getLastRoute_();
    if (lastRoute.isDone()) throw ExceptionType("Trying to update already finished route", __FILE__, __FUNCTION__, __LINE__);
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
        }
    }

    // Throw an exception on error
    throw ExceptionType("Invalid key", __FILE__, __FUNCTION__, __LINE__);
}

void Configuration::copyData_(const Configuration& other){
    servers_ = (other.servers_) ? new ServersContainerType(*other.servers_) : NULL;
}
void Configuration::deleteData_(){
    delete servers_;

    servers_ = NULL;
}

}
