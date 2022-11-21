#include "../../include/configurations/route_configuration.hpp"

namespace configuration {

RouteConfiguration::RouteConfiguration(){
    isDone_ = false;
    methods_ = NULL;
    redirection_ = NULL;
    directory_ = NULL;
    directory_listening_ = false;
    default_if_directory_response_path_ = NULL;
    cgi_script_path_ = NULL;
    cgi_bin_path_ = NULL;
    saveFiles_ = false;
    saveTo_ = NULL;
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

void RouteConfiguration::setMethods(const MethodsContainerType& methods){
    throwOnDone();
    if (!methods_) methods_ = new MethodsContainerType(methods);
    else *methods_ = methods; 
}
RouteConfiguration::MethodsContainerType& RouteConfiguration::getMethods(){
    if (methods_) return *methods_;
    throw ExceptionType("Methods are not defined", __FILE__, __FUNCTION__, __LINE__);
}
const RouteConfiguration::MethodsContainerType& RouteConfiguration::getMethods() const{
    if (methods_) return *methods_;
    throw ExceptionType("Methods are not defined", __FILE__, __FUNCTION__, __LINE__);
}
void RouteConfiguration::setMethod(const MethodType& method, SizeType position){
    throwOnDone();
    if (methods_) methods_->at(position) = method;
    else throw ExceptionType("Methods are not defined", __FILE__, __FUNCTION__, __LINE__);
}
RouteConfiguration::MethodType& RouteConfiguration::getMethod(SizeType position){
    if (methods_) return methods_->at(position);
    else throw ExceptionType("Methods are not defined", __FILE__, __FUNCTION__, __LINE__);
}
const RouteConfiguration::MethodType& RouteConfiguration::getMethod(SizeType position) const{
    if (methods_) return methods_->at(position);
    else throw ExceptionType("Methods are not defined", __FILE__, __FUNCTION__, __LINE__);
}
void RouteConfiguration::addMethod(const MethodType& method){
    throwOnDone();
    if (!methods_) methods_ = new MethodsContainerType();
    methods_->push_back(method);
}
RouteConfiguration::SizeType RouteConfiguration::getMethodsCount() const{
    if (methods_) return methods_->size();
    else throw ExceptionType("Methods are not defined", __FILE__, __FUNCTION__, __LINE__);
}

void RouteConfiguration::setRedirection(const PathType& redirection){
    throwOnDone();
    if (!redirection_) redirection_ = new PathType(redirection);
    else *redirection_ = redirection;
}
RouteConfiguration::PathType& RouteConfiguration::getRedirection(){
    if (redirection_) return *redirection_;
    throw ExceptionType("Redirection is not defined", __FILE__, __FUNCTION__, __LINE__);
}
const RouteConfiguration::PathType& RouteConfiguration::getRedirection() const{
    if (redirection_) return *redirection_;
    throw ExceptionType("Redirection is not defined", __FILE__, __FUNCTION__, __LINE__);
}

void RouteConfiguration::setDirectory(const PathType& directory){
    throwOnDone();
    if (!directory_) directory_ = new PathType(directory);
    else *directory_ = directory;
}
RouteConfiguration::PathType& RouteConfiguration::getDirectory(){
    if (directory_) return *directory_;
    throw ExceptionType("Directory is not defined", __FILE__, __FUNCTION__, __LINE__);
}
const RouteConfiguration::PathType& RouteConfiguration::getDirectory() const{
    if (directory_) return *directory_;
    throw ExceptionType("Directory is not defined", __FILE__, __FUNCTION__, __LINE__);
}

void RouteConfiguration::setDirectoryListening(bool directoryListening){
    throwOnDone();
    directory_listening_ = directoryListening;
}
bool RouteConfiguration::getDirectoryListening() const{
    return directory_listening_;
}

void RouteConfiguration::setDefaultIfDirectoryResponse(const PathType& default_if_directory_response_path){
    throwOnDone();
    if (!default_if_directory_response_path_) default_if_directory_response_path_ = new PathType(default_if_directory_response_path);
    else *default_if_directory_response_path_ = default_if_directory_response_path;
}
RouteConfiguration::PathType& RouteConfiguration::getDefaultIfDirectoryResponse(){
    if (default_if_directory_response_path_) return *default_if_directory_response_path_;
    throw ExceptionType("Default directory is not defined", __FILE__, __FUNCTION__, __LINE__);
}
const RouteConfiguration::PathType& RouteConfiguration::getDefaultIfDirectoryResponse() const{
    if (default_if_directory_response_path_) return *default_if_directory_response_path_;
    throw ExceptionType("Default directory is not defined", __FILE__, __FUNCTION__, __LINE__);
}

void RouteConfiguration::setCgiScriptPath(const PathType& cgi_script_path){
    throwOnDone();
    if (!cgi_script_path_) cgi_script_path_ = new PathType(cgi_script_path);
    else *cgi_script_path_ = cgi_script_path;
}
RouteConfiguration::PathType& RouteConfiguration::getCgiScriptPath(){
    if (cgi_script_path_) return *cgi_script_path_;
    throw ExceptionType("CGI script path is not defined", __FILE__, __FUNCTION__, __LINE__);
}
const RouteConfiguration::PathType& RouteConfiguration::getCgiScriptPath() const{
    if (cgi_script_path_) return *cgi_script_path_;
    throw ExceptionType("CGI script path is not defined", __FILE__, __FUNCTION__, __LINE__);
}

void RouteConfiguration::setCgiBinPath(const PathType& cgi_bin_path){
    throwOnDone();
    if (!cgi_bin_path_) cgi_bin_path_ = new PathType(cgi_bin_path);
    else *cgi_bin_path_ = cgi_bin_path;
}
RouteConfiguration::PathType& RouteConfiguration::getCgiBinPath(){
    if (cgi_bin_path_) return *cgi_bin_path_;
    throw ExceptionType("CGI bin path is not defined", __FILE__, __FUNCTION__, __LINE__);
}
const RouteConfiguration::PathType& RouteConfiguration::getCgiBinPath() const{
    if (cgi_bin_path_) return *cgi_bin_path_;
    throw ExceptionType("CGI bin path is not defined", __FILE__, __FUNCTION__, __LINE__);
}

void RouteConfiguration::setSaveFiles(bool saveFiles){
    throwOnDone();
    saveFiles_ = saveFiles;
}
bool RouteConfiguration::getSaveFiles() const{
    return saveFiles_;
}

void RouteConfiguration::setSaveTo(const PathType& saveTo){
    throwOnDone();
    if (!saveTo_) saveTo_ = new PathType(saveTo);
    else *saveTo_ = saveTo;
}
RouteConfiguration::PathType& RouteConfiguration::getSaveTo(){
    if (saveTo_) return *saveTo_;
    throw ExceptionType("Path to save files is not defined", __FILE__, __FUNCTION__, __LINE__);
}
const RouteConfiguration::PathType& RouteConfiguration::getSaveTo() const{
    if (saveTo_) return *saveTo_;
    throw ExceptionType("Path to save files is not defined", __FILE__, __FUNCTION__, __LINE__);
}

bool RouteConfiguration::isDone() const{
    return isDone_;
}
void RouteConfiguration::done(){
    checkValidity_();
    isDone_ = true;
}

RouteConfiguration* RouteConfiguration::getObject(){
    return new RouteConfiguration();
}
RouteConfiguration* RouteConfiguration::getObject(const RouteConfiguration& other){
    return new RouteConfiguration(other);
}

void RouteConfiguration::deleteData_(){
    delete methods_;
    delete redirection_;
    delete directory_;
    delete default_if_directory_response_path_;
    delete cgi_script_path_;
    delete cgi_bin_path_;
    delete saveTo_;

    isDone_ = false;
    methods_ = NULL;
    redirection_ = NULL;
    directory_ = NULL;
    directory_listening_ = false;
    default_if_directory_response_path_ = NULL;
    cgi_script_path_ = NULL;
    cgi_bin_path_ = NULL;
    saveFiles_ = false;
    saveTo_ = NULL;
}
void RouteConfiguration::copyData_(const RouteConfiguration& other){
    isDone_ = other.isDone_;
    methods_ = (other.methods_) ? new MethodsContainerType(*other.methods_) : NULL;
    redirection_ = (other.redirection_) ? new PathType(*other.redirection_) : NULL;
    directory_ = (other.directory_) ? new PathType(*other.directory_) : NULL;
    directory_listening_ = other.directory_listening_;
    default_if_directory_response_path_ = (other.default_if_directory_response_path_) ? new PathType(*other.default_if_directory_response_path_) : NULL;
    cgi_script_path_ = (other.cgi_script_path_) ? new PathType(*other.cgi_script_path_) : NULL;
    cgi_bin_path_ = (other.cgi_bin_path_) ? new PathType(*other.cgi_bin_path_) : NULL;
    saveFiles_ = other.saveFiles_;
    saveTo_ = (other.saveTo_) ? new PathType(*other.saveTo_) : NULL;
}
void RouteConfiguration::checkValidity_() const{
    if (!methods_ || !methods_->size()) throw ExceptionType("Server methods are not set up", __FILE__, __FUNCTION__, __LINE__);
    if (!redirection_) throw ExceptionType("HTTP redirection is not set up", __FILE__, __FUNCTION__, __LINE__);
    if (!directory_) throw ExceptionType("Server directory is not set up", __FILE__, __FUNCTION__, __LINE__);
    if (directory_listening_ && !default_if_directory_response_path_) throw ExceptionType("ifDirectoryReplyPage is not set up", __FILE__, __FUNCTION__, __LINE__);
    if (saveFiles_ && !saveTo_) throw ExceptionType("Path for uploading files is not set up", __FILE__, __FUNCTION__, __LINE__);
    if (cgi_script_path_ && !cgi_bin_path_) throw ExceptionType("CGI bin is not set for CGI script", __FILE__, __FUNCTION__, __LINE__);
}
void RouteConfiguration::throwOnDone() const{
    if (isDone_) throw ExceptionType("Route is done. You cannot change it anymore.", __FILE__, __FUNCTION__, __LINE__);
}

}
