#pragma once

#include <cctype>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

enum CONFIG_ELEM{
    PORT,
    HOST,
    SERVER_NAME,
    ERROR_PAGES,
    BODY_SIZE,
    METHODS,
    REDIR,
    DIR,
    DIR_LISTENING,
    DEF_IF_DIR,
    CGI_SCRIPT,
    CGI_BIN
};

enum HTTP_METHOD{
    GET,
    POST,
    DELETE
};

class Exception {
public:
    Exception(const char* msg)
        : msg_(std::string(msg)) {

    }
    Exception(const std::string& msg)
        : msg_(msg) {

    }
    ~Exception() throw(){

    }

    virtual const char* what() const throw(){
        return output_().c_str();
    }

protected:
    const std::string msg_;

    virtual std::string output_() const {
        return "EXCEPTION: " + msg_;
    }
};

class ConfigurationException : public Exception {
public:
    ConfigurationException(const char* msg) : Exception(msg){}
    ConfigurationException(const std::string& msg) : Exception(msg) {}

protected:
    virtual std::string output_() const {
        return "CONFIGURATION_EXCEPTION: " + msg_;
    }

};

class ServerException : public Exception {
public:
    ServerException(const char* msg) : Exception(msg) {}
    ServerException(const std::string& msg) : Exception(msg) {}

protected:
    std::string output_() const {
        return "SERVER_EXCEPTION: " + msg_;
    }

};

class RouteException : public Exception {
public:
    RouteException(const char* msg) : Exception(msg) {}
    RouteException(const std::string& msg) : Exception(msg) {}

protected:
    std::string output_() const {
        return "ROUTE_EXCEPTION: " + msg_;
    }

};

// This class contains IP address
class ConfigurationHost{
public:
    typedef unsigned char   VALUE_TYPE;
    typedef size_t          SIZE_TYPE;

    ConfigurationHost(VALUE_TYPE b1, VALUE_TYPE b2, VALUE_TYPE b3, VALUE_TYPE b4){
        ip_[0] = b1;
        ip_[1] = b2;
        ip_[2] = b3;
        ip_[3] = b4;
    }
    ConfigurationHost(const ConfigurationHost& other){
        operator=(other);
    }
    ConfigurationHost(const std::string& hostStr){
        operator=(hostStr);
    }

    ConfigurationHost& operator=(const ConfigurationHost& other){
        for (SIZE_TYPE i = 0; i < maxSize_; i++) ip_[i] = other.ip_[i];
        return *this;
    }
    ConfigurationHost& operator=(const std::string& hostStr){
        const std::string errorStr = "Invalid host string";
        SIZE_TYPE counter = 0;
        VALUE_TYPE numbers[maxSize_];

        std::string::const_iterator begin = hostStr.begin();
        while (counter < maxSize_){
            std::string::const_iterator end = std::find(begin, hostStr.end(), '.');
            std::string substr = hostStr.substr(
                std::distance(hostStr.begin(), begin),  // position of substring beginning
                std::distance(begin, end)               // substring length
            );

            numbers[counter++] = toNum_(substr);
            if ((counter == maxSize_ && end != hostStr.end()) || 
                    (counter != maxSize_ && end == hostStr.end())){
                throw ConfigurationException(errorStr);
            }

            begin = ++end;
        }

        if (counter != maxSize_) throw ConfigurationException(errorStr);
        for (SIZE_TYPE i = 0; i < maxSize_; i++) ip_[i] = numbers[i];
        return *this;
    }

    // Return string representation of IP address.
    std::string toString() const {
        std::string str = "";

        for (SIZE_TYPE i = 0; i < maxSize_; i++){
            str += toString_(ip_[i]);
            if (i + 1 != maxSize_){
                str += '.';
            }
        }

        return str;
    }
    // Get number from IP at specified position.
    // May throw an exception on error.
    VALUE_TYPE at(SIZE_TYPE position) const {
        if (position > maxSize_) throw ConfigurationException("Bad IP position");
        return ip_[position];
    }

    // Set IP number to specified position.
    void set(VALUE_TYPE value, SIZE_TYPE position){
        if (position > maxSize_) throw ConfigurationException("Bad IP position");
        ip_[position] = value;  
    }

private:
    const static SIZE_TYPE maxSize_ = 4;
    VALUE_TYPE ip_[maxSize_];

    // Convert VALUE_TYPE to string.
    std::string toString_(VALUE_TYPE val) const {
        if (val == 0) return "0";
        
        std::string result = "";

        while (val > 0){
            result += '0' + val % 10;
            val /= 10;
        }

        std::reverse(result.begin(), result.end());
        return result;
    }

    // Convert string number to VALUE_TYPE.
    // May throw exception.
    VALUE_TYPE toNum_(const std::string& str) const {
        const std::string errorStr = "Invalid host value";
        if (!str.size()) throw ConfigurationException(errorStr);

        int res = 0;
        for (SIZE_TYPE i = 0; i < str.size(); i++){
            char c = str.at(i);
            if (c < '0' || c > '9') throw ConfigurationException(errorStr);
            res = res * 10 + (str.at(i) - '0');
        }

        if (res < 0 || res > 255) throw ConfigurationException(errorStr);
        return static_cast<VALUE_TYPE>(res);
    }

};

class RouteConfiguration{
public:
    typedef size_t                      SIZE_TYPE;
    typedef int                         METHOD_TYPE;
    typedef std::vector<METHOD_TYPE>    METHODS_CONTAINER_TYPE;
    typedef std::string                 PATH_TYPE;

    RouteConfiguration(){
        isDone_ = false;
        methods_ = NULL;
        redirection_ = NULL;
        directory_ = NULL;
        directory_listening_ = false;
        default_if_directory_response_path_ = NULL;
        cgi_script_path_ = NULL;
        cgi_bin_path_ = NULL;
    }
    RouteConfiguration(const RouteConfiguration& other){
        isDone_ = other.isDone_;
        methods_ = (other.methods_) ? new METHODS_CONTAINER_TYPE(*other.methods_) : NULL;
        redirection_ = (other.redirection_) ? new PATH_TYPE(*other.redirection_) : NULL;
        directory_ = (other.directory_) ? new PATH_TYPE(*other.directory_) : NULL;
        directory_listening_ = other.directory_listening_;
        default_if_directory_response_path_ = (other.default_if_directory_response_path_) ? new PATH_TYPE(*other.default_if_directory_response_path_) : NULL;
        cgi_script_path_ = (other.cgi_script_path_) ? new PATH_TYPE(*other.cgi_script_path_) : NULL;
        cgi_bin_path_ = (other.cgi_bin_path_) ? new PATH_TYPE(*other.cgi_bin_path_) : NULL;
    }
    ~RouteConfiguration(){
        deleteData_();
    }

    RouteConfiguration& operator=(const RouteConfiguration& other){
        deleteData_();

        isDone_ = other.isDone_;
        methods_ = (other.methods_) ? new METHODS_CONTAINER_TYPE(*other.methods_) : NULL;
        redirection_ = (other.redirection_) ? new PATH_TYPE(*other.redirection_) : NULL;
        directory_ = (other.directory_) ? new PATH_TYPE(*other.directory_) : NULL;
        directory_listening_ = other.directory_listening_;
        default_if_directory_response_path_ = (other.default_if_directory_response_path_) ? new PATH_TYPE(*other.default_if_directory_response_path_) : NULL;
        cgi_script_path_ = (other.cgi_script_path_) ? new PATH_TYPE(*other.cgi_script_path_) : NULL;
        cgi_bin_path_ = (other.cgi_bin_path_) ? new PATH_TYPE(*other.cgi_bin_path_) : NULL;

        return *this;        
    }

    void setMethods(const METHODS_CONTAINER_TYPE& methods){
        if (!methods_) methods_ = new METHODS_CONTAINER_TYPE(methods);
        else *methods_ = methods; 
    }
    METHODS_CONTAINER_TYPE& getMethods() const{
        if (methods_) return *methods_;
        throw RouteException("Methods are not defined");
    }
    void setMethod(const METHOD_TYPE& method, SIZE_TYPE position){
        if (methods_) methods_->at(position) = method;
        else throw RouteException("Methods are not defined");
    }
    METHOD_TYPE& getMethod(SIZE_TYPE position) const{
        if (methods_) return methods_->at(position);
        else throw RouteException("Methods are not defined");
    }
    void addMethod(const METHOD_TYPE& method){
        if (!methods_) methods_ = new METHODS_CONTAINER_TYPE();
        methods_->push_back(method);
    }
    SIZE_TYPE getMethodsCount() const{
        if (methods_) return methods_->size();
        else throw RouteException("Methods are not defined");
    }

    void setRedirection(const PATH_TYPE& redirection){
        if (!redirection_) redirection_ = new PATH_TYPE(redirection);
        else *redirection_ = redirection;
    }
    PATH_TYPE& getRedirection() const{
        if (redirection_) return *redirection_;
        throw RouteException("Redirection is not defined");
    }

    void setDirectory(const PATH_TYPE& directory){
        if (!directory_) directory_ = new PATH_TYPE(directory);
        else *directory_ = directory;
    }
    PATH_TYPE& getDirectory() const{
        if (directory_) return *directory_;
        throw RouteException("Directory is not defined");
    }

    void setDirectoryListening(bool directoryListening){
        directory_listening_ = directoryListening;
    }
    bool getDirectoryListening() const{
        return directory_listening_;
    }

    void setDefaultIfDirectoryResponse(const PATH_TYPE& default_if_directory_response_path){
        if (!default_if_directory_response_path_) default_if_directory_response_path_ = new PATH_TYPE(default_if_directory_response_path);
        else *default_if_directory_response_path_ = default_if_directory_response_path;
    }
    PATH_TYPE& getDefaultIfDirectoryResponse() const{
        if (default_if_directory_response_path_) return *default_if_directory_response_path_;
        throw RouteException("Default directory is not defined");
    }

    void setCgiScriptPath(const PATH_TYPE& cgi_script_path){
        if (!cgi_script_path_) cgi_script_path_ = new PATH_TYPE(cgi_script_path);
        else *cgi_script_path_ = cgi_script_path;
    }
    PATH_TYPE& getCgiScriptPath() const{
        if (cgi_script_path_) return *cgi_script_path_;
        throw RouteException("CGI script path is not defined");
    }

    void setCgiBinPath(const PATH_TYPE& cgi_bin_path){
        if (!cgi_bin_path_) cgi_bin_path_ = new PATH_TYPE(cgi_bin_path);
        else *cgi_bin_path_ = cgi_bin_path;
    }
    PATH_TYPE& getCgiBinPath() const{
        if (cgi_bin_path_) return *cgi_bin_path_;
        else RouteException("CGI bin path is not defined");
    }

    bool isDone() const{
        return isDone_;
    }
    void done(){
        isDone_ = true;
    }

private:
    bool isDone_;
    METHODS_CONTAINER_TYPE* methods_;
    PATH_TYPE* redirection_;
    PATH_TYPE* directory_;
    bool directory_listening_;
    PATH_TYPE* default_if_directory_response_path_;
    PATH_TYPE* cgi_script_path_;
    PATH_TYPE* cgi_bin_path_;

    void deleteData_(){
        delete methods_;
        delete redirection_;
        delete directory_;
        delete default_if_directory_response_path_;
        delete cgi_script_path_;
        delete cgi_bin_path_;

        isDone_ = false;
        methods_ = NULL;
        redirection_ = NULL;
        directory_ = NULL;
        directory_listening_ = false;
        default_if_directory_response_path_ = NULL;
        cgi_script_path_ = NULL;
        cgi_bin_path_ = NULL;
    }

};

class ServerConfiguration{
public:
    typedef size_t                          SIZE_TYPE;
    typedef unsigned short                  PORT_TYPE;
    typedef ConfigurationHost               HOST_TYPE;
    typedef std::string                     SERVER_NAME_TYPE;
    typedef std::string                     ERROR_PAGE_TYPE;
    typedef std::vector<ERROR_PAGE_TYPE>    ERROR_PAGES_CONTAINER_TYPE;
    typedef SIZE_TYPE                       BODY_SIZE_TYPE;
    typedef RouteConfiguration              ROUTE_TYPE;
    typedef std::vector<ROUTE_TYPE>         ROUTES_CONTAINER_TYPE;

    ServerConfiguration(){
        isDone_ = false;
        port_ = NULL;
        host_ = NULL;
        serverName_ = NULL;
        errorPages_ = NULL;
        bodySize_ = 0;
        routes_ = NULL;
    }
    ServerConfiguration(const ServerConfiguration& other){
        isDone_ = other.isDone_;
        port_ = (other.port_) ? new PORT_TYPE(*other.port_) : NULL;
        host_ = (other.host_) ? new HOST_TYPE(*other.host_) : NULL;
        serverName_ = (other.serverName_) ? new SERVER_NAME_TYPE(*other.serverName_) : NULL;
        errorPages_ = (other.errorPages_) ? new ERROR_PAGES_CONTAINER_TYPE(*other.errorPages_) : NULL;
        bodySize_ = other.bodySize_;
        routes_ = (other.routes_) ? new ROUTES_CONTAINER_TYPE(*other.routes_) : NULL;
    }
    ~ServerConfiguration(){
        deleteData_();
    }

    ServerConfiguration& operator=(const ServerConfiguration& other){
        deleteData_();

        isDone_ = other.isDone_;
        port_ = (other.port_) ? new PORT_TYPE(*other.port_) : NULL;
        host_ = (other.host_) ? new HOST_TYPE(*other.host_) : NULL;
        serverName_ = (other.serverName_) ? new SERVER_NAME_TYPE(*other.serverName_) : NULL;
        errorPages_ = (other.errorPages_) ? new ERROR_PAGES_CONTAINER_TYPE(*other.errorPages_) : NULL;
        bodySize_ = other.bodySize_;
        routes_ = (other.routes_) ? new ROUTES_CONTAINER_TYPE(*other.routes_) : NULL;

        return *this;
    }

    void setPort(PORT_TYPE port){
        if (!port_) port_ = new PORT_TYPE(port);
        else *port_ = port;
    }
    PORT_TYPE getPort() const{
        if (port_) return *port_;
        throw ServerException("Port is not defined");
    }

    void setHost(const HOST_TYPE& host){
        if (!host_) host_ = new HOST_TYPE(host);
        else *host_ = host;
    }
    HOST_TYPE& getHost() const{
        if (host_) return *host_;
        throw ServerException("Host is not defined");
    }

    void setServerName(const SERVER_NAME_TYPE& serverName){
        if (!serverName_) serverName_ = new SERVER_NAME_TYPE(serverName);
        else *serverName_ = serverName; 
    }
    SERVER_NAME_TYPE& getServerName() const{
        if (serverName_) return *serverName_;
        throw ServerException("Server name is not defined");
    }

    void setErrorPages(const ERROR_PAGES_CONTAINER_TYPE& errorPages){
        if (!errorPages_) errorPages_ = new ERROR_PAGES_CONTAINER_TYPE(errorPages);
        else *errorPages_ = errorPages;
    }
    ERROR_PAGES_CONTAINER_TYPE& getErrorPages() const{
        if (errorPages_) return *errorPages_;
        throw ServerException("Error pages are not defined");
    }
    void setErrorPage(const ERROR_PAGE_TYPE& errorPage, SIZE_TYPE position){
        if (errorPages_) errorPages_->at(position) = errorPage;
        else throw ServerException("Error pages are not defined");
    }
    ERROR_PAGE_TYPE& getErrorPage(SIZE_TYPE position){
        if (errorPages_) return errorPages_->at(position);
        else throw ServerException("Error pages are not defined");
    }
    void addErrorPage(const ERROR_PAGE_TYPE& errorPage){
        if (!errorPages_) errorPages_ = new  ERROR_PAGES_CONTAINER_TYPE();
        errorPages_->push_back(errorPage);        
    }
    SIZE_TYPE getErrorPagesCount() const{
        if (errorPages_) return errorPages_->size();
        else throw ServerException("Error pages are not defined");
    }

    void setBodySize(BODY_SIZE_TYPE bodySize){
        bodySize_ = bodySize;
    }
    BODY_SIZE_TYPE getBodySizse() const{
        return bodySize_;
    }

    void setRoutes(const ROUTES_CONTAINER_TYPE& routes){
        if (!routes_) routes_ = new ROUTES_CONTAINER_TYPE(routes);
        else *routes_ = routes;
    }
    ROUTES_CONTAINER_TYPE& getRoutes() const{
        if (routes_) return *routes_;
        throw ServerException("Routes are not defined");
    }
    void setRoute(const ROUTE_TYPE& route, SIZE_TYPE position){
        if (routes_) routes_->at(position) = route;
        throw ServerException("Routes are not defined");
    }
    ROUTE_TYPE& getRoute(SIZE_TYPE position) const{
        if (routes_) return routes_->at(position);
        throw ServerException("Routes are not defined");
    }
    void addRoute(const ROUTE_TYPE& route){
        if (!routes_) routes_ = new ROUTES_CONTAINER_TYPE();
        routes_->push_back(route);
    }
    SIZE_TYPE getRoutesCount() const{
        if (routes_) return routes_->size();
        throw ServerException("Routes are not defined");
    }

    bool isDone() const{
        return isDone_;
    }
    void done(){
        isDone_ = true;
    }

private:
    bool isDone_;
    PORT_TYPE* port_;
    HOST_TYPE* host_;
    SERVER_NAME_TYPE* serverName_;
    ERROR_PAGES_CONTAINER_TYPE* errorPages_;
    BODY_SIZE_TYPE bodySize_;
    ROUTES_CONTAINER_TYPE* routes_;

    void deleteData_(){
        delete port_;
        delete host_;
        delete serverName_;
        delete errorPages_;
        delete routes_;

        isDone_ = false;
        port_ = NULL;
        host_ = NULL;
        serverName_ = NULL;
        errorPages_ = NULL;
        bodySize_  = 0;
        routes_ = NULL;
    }

};

// This class contains all info from
// configuration file
class Configuration{
public:
    typedef ServerConfiguration SERVER_TYPE;

    Configuration(){

    }
    Configuration(const Configuration& other){
        operator=(other);
    }
    ~Configuration(){

    }

    Configuration& operator=(const Configuration& other){
        servers_ = other.servers_;
        return *this;
    }

    // Parse configuration file.
    // May throw exception on error.
    void parseFile(const std::string& inputFile){
        typedef std::string::iterator Iterator;

        const std::string errorMsg = "Configuration file parsing error";
        std::ifstream inputFileStream(inputFile.c_str(), std::ios::in);
        if (!inputFileStream.is_open()) throw ConfigurationException("Unable to open input file: " + inputFile);

        std::string line;
        while(std::getline(inputFileStream, line)){     // it does not have whitespaces here anymore    
            if (isLineEmpty_(line)) continue;
            line.resize(std::distance(line.begin(), std::remove_if(line.begin(), line.end(), isspace)));    // Remove whitespaces from line

            Iterator iter = line.begin();
            while (iter != line.end()){
                char c = *iter;

                if (c == '{'){          // Start server

                    try {
                        SERVER_TYPE& lastServer = getLastServer();
                        if (!lastServer.isDone()) throw Exception(errorMsg);
                        servers_.push_back(SERVER_TYPE());
                    } catch (ConfigurationException&){
                        servers_.push_back(SERVER_TYPE());
                    } catch (Exception&){
                        throw;
                    }

                } else if (c == '}'){   // Finish server

                    try {
                        SERVER_TYPE& lastServer = getLastServer();
                        if (lastServer.isDone()) throw Exception(errorMsg);
                        if (!getLastRoute().isDone()) throw Exception(errorMsg);
                        lastServer.done();
                    } catch (ServerException&){
                        getLastServer().done();
                    } catch (ConfigurationException&){
                        throw;
                    } catch (Exception&){
                        throw;
                    }

                } else if (c == '['){   // Start route for last server

                    try {
                        SERVER_TYPE& lastServer = getLastServer();
                        if (lastServer.isDone()) throw Exception(errorMsg);
                        if (!getLastRoute().isDone()) throw Exception(errorMsg);
                        lastServer.addRoute(SERVER_TYPE::ROUTE_TYPE());
                    } catch (ServerException&){
                        getLastServer().addRoute(SERVER_TYPE::ROUTE_TYPE());
                    } catch (ConfigurationException&){
                        throw;
                    } catch (Exception&){
                        throw;
                    }

                } else if (c == ']'){   // Finish route for last server

                    try {
                        SERVER_TYPE& lastServer = getLastServer();
                        if (lastServer.isDone()) throw Exception(errorMsg);
                        if (getLastRoute().isDone()) throw Exception(errorMsg);
                        getLastRoute().done();
                    } catch (ServerException&){
                        throw;
                    } catch (ConfigurationException&){
                        throw;
                    } catch (Exception&){
                        throw;
                    }

                } else {                // value string

                    Iterator begin = iter;
                    Iterator end = std::find(begin, line.end(), ';');
                    if (end == line.end()) throw ConfigurationException(errorMsg);  // Did not find ';' == very bad
                    
                    std::string substring = line.substr(
                        std::distance(line.begin(), begin),
                        std::distance(begin, end)
                    );

                    if (end == line.end()) break;
                    iter = ++end;
                    continue;

                }

                iter++;
            }
        }

        inputFileStream.close();
    }

private:
    std::vector<SERVER_TYPE> servers_;

    // Check if string contains only whitespaces
    bool isLineEmpty_(const std::string& line) const{
        if (!line.size()) return true;
        for (size_t i = 0; i < line.size(); i++){
            if (!std::isspace(line[i])) return false;
        }
        return true;
    }

    SERVER_TYPE& getLastServer(){
        if (!servers_.size()) throw ConfigurationException("Servers are not defined");
        return servers_.back();
    }
    SERVER_TYPE::ROUTE_TYPE& getLastRoute(){
        return getLastServer().getRoutes().back();
    }

};
