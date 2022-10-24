/*
#include "../../include/configuration.hpp"

ConfigurationException::ConfigurationException(const char* msg)
        : msg_(createMsg_(msg)) {

}
ConfigurationException::ConfigurationException(const std::string& msg)
        : msg_(createMsg_(msg)) {

}
ConfigurationException::~ConfigurationException() throw(){

}
const char* ConfigurationException::what() const throw(){
    return msg_.c_str();
}
const std::string ConfigurationException::createMsg_(const std::string& msg) const{
    return "CONFIGURATION ERROR: " + msg;
}
const std::string ConfigurationException::createMsg_(const char* msg) const{
    return createMsg_(std::string(msg));
}

// *********************************************************************************

RouteConfiguration::RouteConfiguration(){

}
RouteConfiguration::RouteConfiguration(const RouteConfiguration& other){
    (void)other;
}
RouteConfiguration::~RouteConfiguration(){

}
RouteConfiguration& RouteConfiguration::operator=(const RouteConfiguration& other){
    return *this;
}

void RouteConfiguration::setMethods(const METHODS_CONTAINER_TYPE& methods){
    (void)methods;
}
RouteConfiguration::METHODS_CONTAINER_TYPE& RouteConfiguration::getMethods() const{

}
void RouteConfiguration::setMethod(const METHOD_TYPE& method, SIZE_TYPE position){

}
RouteConfiguration::METHOD_TYPE& RouteConfiguration::getMethod(SIZE_TYPE position) const{

}
RouteConfiguration::SIZE_TYPE RouteConfiguration::getMethodsCount() const{

}
void RouteConfiguration::setRedirection(const PATH_TYPE& redirection){

}
RouteConfiguration::PATH_TYPE& RouteConfiguration::getRedirection() const{

}

void RouteConfiguration::setDirectory(const PATH_TYPE& directory){

}
RouteConfiguration::PATH_TYPE& RouteConfiguration::getDirectory() const{

}

void RouteConfiguration::setDirectoryListening(bool directoryListening){

}
bool RouteConfiguration::getDirectoryListening() const{

}

void RouteConfiguration::setDefaultIfDirectoryResponse(const PATH_TYPE& default_if_directory_response_path){

}
RouteConfiguration::PATH_TYPE& RouteConfiguration::getDefaultIfDirectoryResponse() const{

}

void RouteConfiguration::setCgiScriptPath(const PATH_TYPE& cgi_script_path){

}
RouteConfiguration::PATH_TYPE& RouteConfiguration::getCgiScriptPath() const{

}

void RouteConfiguration::setCgiBinPath(const PATH_TYPE& cgi_bin_path){

}
RouteConfiguration::PATH_TYPE& RouteConfiguration::getCgiBinPath() const{

}

bool RouteConfiguration::isDone() const{

}

// *********************************************************************************

ServerConfiguration::ServerConfiguration(){
    isDone_ = false;
    port_ = NULL;
    host_ = NULL;
    serverName_ = NULL;
    errorPages_ = NULL;
    bodySize_ = 0;
    routes_ = NULL;
}
ServerConfiguration::ServerConfiguration(const ServerConfiguration& other){
    isDone_ = other.isDone_;
    port_ = (other.port_) ? new PORT_TYPE(*other.port_) : NULL;
    host_ = (other.host_) ? new HOST_TYPE(*other.host_) : NULL;
    serverName_ = (other.serverName_) ? new SERVER_NAME_TYPE(*other.serverName_) : NULL;
    errorPages_ = (other.errorPages_) ? new ERROR_PAGES_CONTAINER_TYPE(*other.errorPages_) : NULL;
    bodySize_ = other.bodySize_;
    routes_ = (other.routes_) ? new ROUTES_CONTAINER_TYPE(*other.routes_) : NULL;
}
ServerConfiguration::~ServerConfiguration(){
    deleteData_();
}

ServerConfiguration& ServerConfiguration::operator=(const ServerConfiguration& other){
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

void ServerConfiguration::setPort(ServerConfiguration::PORT_TYPE port){
    if (!port_) port_ = new PORT_TYPE(port);
    else *port_ = port;
}
ServerConfiguration::PORT_TYPE ServerConfiguration::getPort() const{
    if (port_) return *port_;
    throw ConfigurationException("Port is not defined");
}

void ServerConfiguration::setHost(const ServerConfiguration::HOST_TYPE& host){
    if (!host_) host_ = new HOST_TYPE(host);
    else *host_ = host;
}
ServerConfiguration::HOST_TYPE& ServerConfiguration::getHost() const{
    if (host_) return *host_;
    throw ConfigurationException("Host is not defined");
}

void ServerConfiguration::setServerName(const ServerConfiguration::SERVER_NAME_TYPE& serverName){
    if (!serverName_) serverName_ = new SERVER_NAME_TYPE(serverName);
    else *serverName_ = serverName; 
}
ServerConfiguration::SERVER_NAME_TYPE& ServerConfiguration::getServerName() const{
    if (serverName_) return *serverName_;
    throw ConfigurationException("Server name is not defined");
}

void ServerConfiguration::setErrorPages(const ServerConfiguration::ERROR_PAGES_CONTAINER_TYPE& errorPages){
    if (!errorPages_) errorPages_ = new ERROR_PAGES_CONTAINER_TYPE(errorPages);
    else *errorPages_ = errorPages;
}
ServerConfiguration::ERROR_PAGES_CONTAINER_TYPE& ServerConfiguration::getErrorPages() const{
    if (errorPages_) return *errorPages_;
    throw ConfigurationException("Error pages are not defined");
}
void ServerConfiguration::setErrorPage(const ServerConfiguration::ERROR_PAGE_TYPE& errorPage, ServerConfiguration::SIZE_TYPE position){
    if (errorPages_) errorPages_->at(position) = errorPage;
    else throw ConfigurationException("Error pages are not defined");
}
ServerConfiguration::ERROR_PAGE_TYPE& ServerConfiguration::getErrorPage(ServerConfiguration::SIZE_TYPE position){
    if (errorPages_) return errorPages_->at(position);
    else throw ConfigurationException("Error pages are not defined");
}
ServerConfiguration::SIZE_TYPE ServerConfiguration::getErrorPagesCount() const{
    if (errorPages_) return errorPages_->size();
    else throw ConfigurationException("Error pages are not defined");
}

void ServerConfiguration::setBodySize(ServerConfiguration::BODY_SIZE_TYPE bodySize){
    bodySize_ = bodySize;
}
ServerConfiguration::BODY_SIZE_TYPE ServerConfiguration::getBodySizse() const{
    return bodySize_;
}

void ServerConfiguration::setRoutes(const ServerConfiguration::ROUTES_CONTAINER_TYPE& routes){
    if (!routes_) routes_ = new ROUTES_CONTAINER_TYPE(routes);
    else *routes_ = routes;
}
ServerConfiguration::ROUTES_CONTAINER_TYPE& ServerConfiguration::getRoutes() const{
    if (routes_) return *routes_;
    throw ConfigurationException("Routes are not defined");
}
void ServerConfiguration::setRoute(const ServerConfiguration::ROUTE_TYPE& route, ServerConfiguration::SIZE_TYPE position){
    if (routes_) routes_->at(position) = route;
    throw ConfigurationException("Routes are not defined");
}
ServerConfiguration::ROUTE_TYPE& ServerConfiguration::getRoute(ServerConfiguration::SIZE_TYPE position) const{
    if (routes_) return routes_->at(position);
    throw ConfigurationException("Routes are not defined");
}
ServerConfiguration::SIZE_TYPE ServerConfiguration::getRoutesCount() const{
    if (routes_) return routes_->size();
    throw ConfigurationException("Routes are not defined");
}

bool ServerConfiguration::isDone() const{
    return isDone_;
}

void ServerConfiguration::deleteData_(){
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

// *********************************************************************************

Configuration::Configuration(){

}
Configuration::Configuration(const Configuration& other){
    (void)other;
}
Configuration::~Configuration(){

}

Configuration& Configuration::operator=(const Configuration& other){
    (void)other;
    return *this;
}
void Configuration::parseFile(const std::string& inputFile){
    std::ifstream inputFileStream(inputFile.c_str(), std::ios::in);
    if (!inputFileStream.is_open()) throw ConfigurationException("unable to open input file: " + inputFile);

    std::string line;
    while(inputFileStream >> line){
        if (isLineEmpty_(line)) continue;


    }
}
bool Configuration::isLineEmpty_(const std::string& line) const{
    if (!line.size()) return true;
    for (size_t i = 0; i < line.size(); i++){
        if (!std::isspace(line[i])) return false;
    }
    return true;
}
*/
