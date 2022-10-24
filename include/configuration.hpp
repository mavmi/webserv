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

enum METHOD{
    GET,
    POST,
    DELETE
};

class ConfigurationException : public std::exception {
public:
    ConfigurationException(const char* msg)
        : msg_(createMsg_(msg)) {

    }
    ConfigurationException(const std::string& msg)
        : msg_(createMsg_(msg)) {

    }
    ~ConfigurationException() throw(){

    }

    virtual const char* what() const throw(){
        return msg_.c_str();
    }

protected:
    const std::string msg_;

private:
    const std::string createMsg_(const std::string& msg) const{
        return "CONFIGURATION ERROR: " + msg;
    }
    const std::string createMsg_(const char* msg) const{
        return createMsg_(std::string(msg));
    }

};

class ConfigurationHost{
public:
    typedef unsigned char   VALUE_TYPE;

    ConfigurationHost(VALUE_TYPE b1, VALUE_TYPE b2, VALUE_TYPE b3, VALUE_TYPE b4)
        : b1_(b1), b2_(b2), b3_(b3), b4_(b4){

    }
    ConfigurationHost(const ConfigurationHost& other){
        b1_ = other.b1_;
        b2_ = other.b2_;
        b3_ = other.b3_;
        b4_ = other.b4_;
    }
    ConfigurationHost(const std::string& hostStr){
        (void)hostStr;
    }

    std::string toString() const {
        return 
            toString_(b1_) + "." +
            toString_(b2_) + "." +
            toString_(b3_) + "." +
            toString_(b4_);
    }

private:
    VALUE_TYPE b1_, b2_, b3_, b4_;

    std::string toString_(VALUE_TYPE val) const {
        std::string result = "";

        while (val > 0){
            result += val % 10;
            val /= 10;
        }

        std::reverse(result.begin(), result.end());
        return result;
    }

};

class RouteConfiguration{
public:
    typedef size_t                      SIZE_TYPE;
    typedef int                         METHOD_TYPE;
    typedef std::vector<METHOD_TYPE>    METHODS_CONTAINER_TYPE;
    typedef std::string                 PATH_TYPE;

    RouteConfiguration();
    RouteConfiguration(const RouteConfiguration& other);
    ~RouteConfiguration();

    RouteConfiguration& operator=(const RouteConfiguration& other);

    void setMethods(const METHODS_CONTAINER_TYPE& methods){
        (void)methods;
    }
    METHODS_CONTAINER_TYPE& getMethods() const{
        return *methods_;
    }
    void setMethod(const METHOD_TYPE& method, SIZE_TYPE position){
        (void)method; (void)position;
    }
    METHOD_TYPE& getMethod(SIZE_TYPE position) const{
        return methods_->at(position);
    }
    SIZE_TYPE getMethodsCount() const{
        return 0;
    }

    void setRedirection(const PATH_TYPE& redirection){
        (void)redirection;
    }
    PATH_TYPE& getRedirection() const{
        return *redirection_;
    }

    void setDirectory(const PATH_TYPE& directory){
        (void)directory;
    }
    PATH_TYPE& getDirectory() const{
        return *directory_;
    }

    void setDirectoryListening(bool directoryListening){
        (void)directoryListening;
    }
    bool getDirectoryListening() const{
        return true;
    }

    void setDefaultIfDirectoryResponse(const PATH_TYPE& default_if_directory_response_path){
        (void)default_if_directory_response_path;
    }
    PATH_TYPE& getDefaultIfDirectoryResponse() const{
        return *default_if_directory_response_path_;
    }

    void setCgiScriptPath(const PATH_TYPE& cgi_script_path){
        (void)cgi_script_path;
    }
    PATH_TYPE& getCgiScriptPath() const{
        return *cgi_script_path_;
    }

    void setCgiBinPath(const PATH_TYPE& cgi_bin_path){
        (void)cgi_bin_path;
    }
    PATH_TYPE& getCgiBinPath() const{
        return *cgi_bin_path_;
    }

    bool isDone() const{
        return isDone_;
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
        throw ConfigurationException("Port is not defined");
    }

    void setHost(const HOST_TYPE& host){
        if (!host_) host_ = new HOST_TYPE(host);
        else *host_ = host;
    }
    HOST_TYPE& getHost() const{
        if (host_) return *host_;
        throw ConfigurationException("Host is not defined");
    }

    void setServerName(const SERVER_NAME_TYPE& serverName){
        if (!serverName_) serverName_ = new SERVER_NAME_TYPE(serverName);
        else *serverName_ = serverName; 
    }
    SERVER_NAME_TYPE& getServerName() const{
        if (serverName_) return *serverName_;
        throw ConfigurationException("Server name is not defined");
    }

    void setErrorPages(const ERROR_PAGES_CONTAINER_TYPE& errorPages){
        if (!errorPages_) errorPages_ = new ERROR_PAGES_CONTAINER_TYPE(errorPages);
        else *errorPages_ = errorPages;
    }
    ERROR_PAGES_CONTAINER_TYPE& getErrorPages() const{
        if (errorPages_) return *errorPages_;
        throw ConfigurationException("Error pages are not defined");
    }
    void setErrorPage(const ERROR_PAGE_TYPE& errorPage, SIZE_TYPE position){
        if (errorPages_) errorPages_->at(position) = errorPage;
        else throw ConfigurationException("Error pages are not defined");
    }
    ERROR_PAGE_TYPE& getErrorPage(SIZE_TYPE position){
        if (errorPages_) return errorPages_->at(position);
        else throw ConfigurationException("Error pages are not defined");
    }
    SIZE_TYPE getErrorPagesCount() const{
        if (errorPages_) return errorPages_->size();
        else throw ConfigurationException("Error pages are not defined");
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
        throw ConfigurationException("Routes are not defined");
    }
    void setRoute(const ROUTE_TYPE& route, SIZE_TYPE position){
        if (routes_) routes_->at(position) = route;
        throw ConfigurationException("Routes are not defined");
    }
    ROUTE_TYPE& getRoute(SIZE_TYPE position) const{
        if (routes_) return routes_->at(position);
        throw ConfigurationException("Routes are not defined");
    }
    SIZE_TYPE getRoutesCount() const{
        if (routes_) return routes_->size();
        throw ConfigurationException("Routes are not defined");
    }

    bool isDone() const{
        return isDone_;
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
    Configuration();
    Configuration(const Configuration& other);
    ~Configuration();

    Configuration& operator=(const Configuration& other){
        (void)other;
        return *this;
    }

    // Parse configuration file.
    // May throw exception on error
    void parseFile(const std::string& inputFile){
        std::ifstream inputFileStream(inputFile.c_str(), std::ios::in);
        if (!inputFileStream.is_open()) throw ConfigurationException("unable to open input file: " + inputFile);

        std::string line;
        while(inputFileStream >> line){
            if (isLineEmpty_(line)) continue;


        }
    }

    Configuration& serverStart();
    Configuration& serverDone();

private:
    std::vector<ServerConfiguration> servers_;

    bool isLineEmpty_(const std::string& line) const{
        if (!line.size()) return true;
        for (size_t i = 0; i < line.size(); i++){
            if (!std::isspace(line[i])) return false;
        }
        return true;
    }

};
