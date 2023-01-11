#include "../../include/configurations/configuration.hpp"

namespace MAIN_NAMESPACE::CONFIG_NAMESPACE{
ConfigurationException::ConfigurationException(const char* msg) : Exception(msg){}
ConfigurationException::ConfigurationException(const std::string& msg) : Exception(msg){}
ConfigurationException::ConfigurationException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
ConfigurationException::ConfigurationException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
ConfigurationException::ConfigurationException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
ConfigurationException::ConfigurationException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string ConfigurationException::output_() const {
    return "CONFIGURATION_EXCEPTION: " + msg_;
}
}


namespace MAIN_NAMESPACE::CONFIG_NAMESPACE{
Configuration::Configuration(){
    servers_ = ServersContainerType();
    hostPortPairs_ = HostPortPairsContainerType();
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
    return servers_;
}
const Configuration::ServersContainerType& Configuration::getServers() const{
    return servers_;
}

const Configuration::ServerType& Configuration::getServer(ServerType::PortType port) const{
    for (ServersContainerType::SizeType i = 0; i < servers_.size(); i++){
        try {
            const ServerType& server = servers_.at(i);
            if (server.getPort() == port) return server;
        } catch (...) {}
    }
    throw ExceptionType("No server with such port", EXC_ARGS);
}
const Configuration::ServerType& Configuration::getServer(const ServerType::HostType& host) const{
    for (ServersContainerType::SizeType i = 0; i < servers_.size(); i++){
        try {
            const ServerType& server = servers_.at(i);
            if (server.getHost() == host) return server;
        } catch (...) {}
    }
    throw ExceptionType("No server with such port", EXC_ARGS);
}
const Configuration::ServerType& Configuration::getServer(ServerType::PortType port, const ServerType::HostType& host) const{
    for (ServersContainerType::SizeType i = 0; i < servers_.size(); i++){
        try {
            const ServerType& server = servers_.at(i);
            if (server.getPort() == port && server.getHost() == host) return server;
        } catch (...) {}
    }
    throw ExceptionType("No server with such port and host", EXC_ARGS);
}

Configuration::ServersContainerType::SizeType Configuration::getServersCount() const {
    return servers_.size();
}
const Configuration::HostPortPairsContainerType& Configuration::getHostPortPairs() const{
    return hostPortPairs_;
}

void Configuration::parseFile(const std::string& inputFile){
    typedef std::string::iterator Iterator;

    std::ifstream inputFileStream(inputFile.c_str(), std::ios::in);
    if (!inputFileStream.is_open()) throw ExceptionType("Unable to open input file: " + inputFile, EXC_ARGS);

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
                    if (!lastServer.isDone()) throw MAIN_NAMESPACE::UTILS_NAMESPACE::Exception("Unable to start server: the previous one is not done", EXC_ARGS);
                    servers_.push_back(ServerType());
                } catch (ExceptionType&){
                    servers_.push_back(ServerType());
                } catch (MAIN_NAMESPACE::UTILS_NAMESPACE::Exception&){
                    throw;
                }

            } else if (c == '}'){   // Finish server

                try {
                    ServerType& lastServer = getLastServer_();
                    if (lastServer.isDone()) throw MAIN_NAMESPACE::UTILS_NAMESPACE::Exception("Unable to finish server: it is already finished", EXC_ARGS);
                    if (!getLastRoute_().isDone()) throw MAIN_NAMESPACE::UTILS_NAMESPACE::Exception("Unable to finish server: it contains unfinished route", EXC_ARGS);
                    lastServer.done();
                    hostPortPairs_.insert(std::make_pair(lastServer.getHost(), lastServer.getPort()));
                } catch (ServerException&){
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
                    lastServer.addRoute(ServerType::RouteType());
                } catch (ServerException&){
                    getLastServer_().addRoute(ServerType::RouteType());
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
                } catch (ServerException&){
                    throw;
                } catch (ExceptionType&){
                    throw;
                } catch (MAIN_NAMESPACE::UTILS_NAMESPACE::Exception&){
                    throw;
                }

            } else {                // value string

                Iterator begin = iter;
                Iterator end = std::find(begin, line.end(), ';');
                if (end == line.end()) throw ExceptionType("Invalid key-value line", EXC_ARGS);  // Did not find ';' == very bad
                
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
    if (!servers_.size()) throw ExceptionType("Servers are not defined", EXC_ARGS);
    return servers_.back();
}
Configuration::ServerType::RouteType& Configuration::getLastRoute_() {
    return getLastServer_().getRoutes().back();
}

Configuration::MethodType Configuration::stringToHttpMethod_(const std::string& str){
    if (str == "GET") return MAIN_NAMESPACE::UTILS_NAMESPACE::GET;
    else if (str == "POST") return MAIN_NAMESPACE::UTILS_NAMESPACE::POST;
    else if (str == "DELETE") return MAIN_NAMESPACE::UTILS_NAMESPACE::DELETE;
    throw ExceptionType("Invalid HTTP method", EXC_ARGS);
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
    throw ExceptionType("Invalid boolean value", EXC_ARGS);
}

std::pair<std::string, std::string> Configuration::split_(const std::string& str) const {
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
void Configuration::parseValueString_(const std::string& str){
    const std::pair<std::string, std::string> key_value = split_(str);
    const std::string& key = key_value.first;
    const std::string& value = key_value.second;

    // Server configs parsing
    ServerType& lastServer = getLastServer_();
    if (lastServer.isDone()) throw ExceptionType("Trying to update already finished server", EXC_ARGS);
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

void Configuration::copyData_(const Configuration& other){
    servers_ = other.servers_;
    hostPortPairs_ = other.hostPortPairs_;
}
void Configuration::deleteData_(){
    servers_ = ServersContainerType();
    hostPortPairs_ = HostPortPairsContainerType();
}
}
