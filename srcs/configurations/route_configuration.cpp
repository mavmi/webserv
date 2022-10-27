#include "../../include/configurations/route_configuration.hpp"

RouteConfiguration::RouteConfiguration(){
    isDone_ = false;
    methods_ = NULL;
    redirection_ = NULL;
    directory_ = NULL;
    directory_listening_ = false;
    default_if_directory_response_path_ = NULL;
    cgi_script_path_ = NULL;
    cgi_bin_path_ = NULL;
}
RouteConfiguration::RouteConfiguration(const RouteConfiguration& other){
    copyData_(other);
}
RouteConfiguration::~RouteConfiguration(){
    deleteData_();
}

RouteConfiguration& RouteConfiguration::operator=(const RouteConfiguration& other){
    deleteData_();
    copyData_(other);
    return *this;        
}

void RouteConfiguration::setMethods(const METHODS_CONTAINER_TYPE& methods){
    if (!methods_) methods_ = new METHODS_CONTAINER_TYPE(methods);
    else *methods_ = methods; 
}
RouteConfiguration::METHODS_CONTAINER_TYPE& RouteConfiguration::getMethods() const{
    if (methods_) return *methods_;
    throw RouteException("Methods are not defined", __FILE__, __FUNCTION__, __LINE__);
}
void RouteConfiguration::setMethod(const METHOD_TYPE& method, SIZE_TYPE position){
    if (methods_) methods_->at(position) = method;
    else throw RouteException("Methods are not defined", __FILE__, __FUNCTION__, __LINE__);
}
RouteConfiguration::METHOD_TYPE& RouteConfiguration::getMethod(SIZE_TYPE position) const{
    if (methods_) return methods_->at(position);
    else throw RouteException("Methods are not defined", __FILE__, __FUNCTION__, __LINE__);
}
void RouteConfiguration::addMethod(const METHOD_TYPE& method){
    if (!methods_) methods_ = new METHODS_CONTAINER_TYPE();
    methods_->push_back(method);
}
RouteConfiguration::SIZE_TYPE RouteConfiguration::getMethodsCount() const{
    if (methods_) return methods_->size();
    else throw RouteException("Methods are not defined", __FILE__, __FUNCTION__, __LINE__);
}

void RouteConfiguration::setRedirection(const PATH_TYPE& redirection){
    if (!redirection_) redirection_ = new PATH_TYPE(redirection);
    else *redirection_ = redirection;
}
RouteConfiguration::PATH_TYPE& RouteConfiguration::getRedirection() const{
    if (redirection_) return *redirection_;
    throw RouteException("Redirection is not defined", __FILE__, __FUNCTION__, __LINE__);
}

void RouteConfiguration::setDirectory(const PATH_TYPE& directory){
    if (!directory_) directory_ = new PATH_TYPE(directory);
    else *directory_ = directory;
}
RouteConfiguration::PATH_TYPE& RouteConfiguration::getDirectory() const{
    if (directory_) return *directory_;
    throw RouteException("Directory is not defined", __FILE__, __FUNCTION__, __LINE__);
}

void RouteConfiguration::setDirectoryListening(bool directoryListening){
    directory_listening_ = directoryListening;
}
bool RouteConfiguration::getDirectoryListening() const{
    return directory_listening_;
}

void RouteConfiguration::setDefaultIfDirectoryResponse(const PATH_TYPE& default_if_directory_response_path){
    if (!default_if_directory_response_path_) default_if_directory_response_path_ = new PATH_TYPE(default_if_directory_response_path);
    else *default_if_directory_response_path_ = default_if_directory_response_path;
}
RouteConfiguration::PATH_TYPE& RouteConfiguration::getDefaultIfDirectoryResponse() const{
    if (default_if_directory_response_path_) return *default_if_directory_response_path_;
    throw RouteException("Default directory is not defined", __FILE__, __FUNCTION__, __LINE__);
}

void RouteConfiguration::setCgiScriptPath(const PATH_TYPE& cgi_script_path){
    if (!cgi_script_path_) cgi_script_path_ = new PATH_TYPE(cgi_script_path);
    else *cgi_script_path_ = cgi_script_path;
}
RouteConfiguration::PATH_TYPE& RouteConfiguration::getCgiScriptPath() const{
    if (cgi_script_path_) return *cgi_script_path_;
    throw RouteException("CGI script path is not defined", __FILE__, __FUNCTION__, __LINE__);
}

void RouteConfiguration::setCgiBinPath(const PATH_TYPE& cgi_bin_path){
    if (!cgi_bin_path_) cgi_bin_path_ = new PATH_TYPE(cgi_bin_path);
    else *cgi_bin_path_ = cgi_bin_path;
}
RouteConfiguration::PATH_TYPE& RouteConfiguration::getCgiBinPath() const{
    if (cgi_bin_path_) return *cgi_bin_path_;
    throw RouteException("CGI bin path is not defined", __FILE__, __FUNCTION__, __LINE__);
}

bool RouteConfiguration::isDone() const{
    return isDone_;
}
void RouteConfiguration::done(){
    isDone_ = true;
}

void RouteConfiguration::deleteData_(){
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
void RouteConfiguration::copyData_(const RouteConfiguration& other){
    isDone_ = other.isDone_;
    methods_ = (other.methods_) ? new METHODS_CONTAINER_TYPE(*other.methods_) : NULL;
    redirection_ = (other.redirection_) ? new PATH_TYPE(*other.redirection_) : NULL;
    directory_ = (other.directory_) ? new PATH_TYPE(*other.directory_) : NULL;
    directory_listening_ = other.directory_listening_;
    default_if_directory_response_path_ = (other.default_if_directory_response_path_) ? new PATH_TYPE(*other.default_if_directory_response_path_) : NULL;
    cgi_script_path_ = (other.cgi_script_path_) ? new PATH_TYPE(*other.cgi_script_path_) : NULL;
    cgi_bin_path_ = (other.cgi_bin_path_) ? new PATH_TYPE(*other.cgi_bin_path_) : NULL;
}

