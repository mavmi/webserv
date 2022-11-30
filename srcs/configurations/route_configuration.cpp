#include "../../include/configurations/route_configuration.hpp"

namespace wsrv::configuration {

RouteConfiguration::RouteConfiguration(){
    isDone_ = false;
    methods_ = Wrapper<MethodsContainerType>();
    redirection_ = Wrapper<PathType>();
    directory_ = Wrapper<PathType>();
    directory_listening_ = false;
    default_if_directory_response_path_ = Wrapper<PathType>();
    cgi_script_path_ = Wrapper<PathType>();
    cgi_bin_path_ = Wrapper<PathType>();
    saveFiles_ = false;
    saveTo_ = Wrapper<PathType>();
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
void* RouteConfiguration::operator new(size_t size){
    return malloc(size);
}
void* RouteConfiguration::operator new(size_t size, const RouteConfiguration& other){
    RouteConfiguration* ptr = (RouteConfiguration*)malloc(size);
    *ptr = other;
    return ptr;
}
void* RouteConfiguration::operator new[](size_t size){
    return malloc(size);
}
void RouteConfiguration::operator delete(void* ptr){
    free(ptr);
}
void RouteConfiguration::operator delete[](void* ptr){
    free(ptr);
}

void RouteConfiguration::setMethods(const MethodsContainerType& methods){
    throwOnDone();
    methods_.set(methods);
}
RouteConfiguration::MethodsContainerType& RouteConfiguration::getMethods(){
    HANDLE_EXC_BEGIN
        return methods_.get();
    HANDLE_EXC_END
}
const RouteConfiguration::MethodsContainerType& RouteConfiguration::getMethods() const{
    HANDLE_EXC_BEGIN
        return methods_.get();
    HANDLE_EXC_END
}
void RouteConfiguration::setMethod(const MethodType& method, SizeType position){
    throwOnDone();
    methods_.get().at(position) = method;
}
RouteConfiguration::MethodType& RouteConfiguration::getMethod(SizeType position){
    HANDLE_EXC_BEGIN
        return methods_.get().at(position);
    HANDLE_EXC_END
}
const RouteConfiguration::MethodType& RouteConfiguration::getMethod(SizeType position) const{
    HANDLE_EXC_BEGIN
        return methods_.get().at(position);
    HANDLE_EXC_END
}
void RouteConfiguration::addMethod(const MethodType& method){
    throwOnDone();
    if (!methods_.isSet()) methods_.set(MethodsContainerType());
    methods_.get().push_back(method);
}
RouteConfiguration::SizeType RouteConfiguration::getMethodsCount() const{
    HANDLE_EXC_BEGIN
        return methods_.get().size();
    HANDLE_EXC_END
}

void RouteConfiguration::setRedirection(const PathType& redirection){
    throwOnDone();
    redirection_.set(redirection);
}
RouteConfiguration::PathType& RouteConfiguration::getRedirection(){
    HANDLE_EXC_BEGIN
        return redirection_.get();
    HANDLE_EXC_END
}
const RouteConfiguration::PathType& RouteConfiguration::getRedirection() const{
    HANDLE_EXC_BEGIN
        return redirection_.get();
    HANDLE_EXC_END
}

void RouteConfiguration::setDirectory(const PathType& directory){
    throwOnDone();
    directory_.set(directory);
}
RouteConfiguration::PathType& RouteConfiguration::getDirectory(){
    HANDLE_EXC_BEGIN
        return directory_.get();
    HANDLE_EXC_END
}
const RouteConfiguration::PathType& RouteConfiguration::getDirectory() const{
    HANDLE_EXC_BEGIN
        return directory_.get();
    HANDLE_EXC_END
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
    default_if_directory_response_path_.set(default_if_directory_response_path);
}
RouteConfiguration::PathType& RouteConfiguration::getDefaultIfDirectoryResponse(){
    HANDLE_EXC_BEGIN
        return default_if_directory_response_path_.get();
    HANDLE_EXC_END
}
const RouteConfiguration::PathType& RouteConfiguration::getDefaultIfDirectoryResponse() const{
    HANDLE_EXC_BEGIN
        return default_if_directory_response_path_.get();
    HANDLE_EXC_END
}

void RouteConfiguration::setCgiScriptPath(const PathType& cgi_script_path){
    throwOnDone();
    cgi_script_path_.set(cgi_script_path);
}
RouteConfiguration::PathType& RouteConfiguration::getCgiScriptPath(){
    HANDLE_EXC_BEGIN
        return cgi_script_path_.get();
    HANDLE_EXC_END
}
const RouteConfiguration::PathType& RouteConfiguration::getCgiScriptPath() const{
    HANDLE_EXC_BEGIN
        return cgi_script_path_.get();
    HANDLE_EXC_END
}

void RouteConfiguration::setCgiBinPath(const PathType& cgi_bin_path){
    throwOnDone();
    cgi_bin_path_.set(cgi_bin_path);
}
RouteConfiguration::PathType& RouteConfiguration::getCgiBinPath(){
    HANDLE_EXC_BEGIN
        return cgi_bin_path_.get();
    HANDLE_EXC_END
}
const RouteConfiguration::PathType& RouteConfiguration::getCgiBinPath() const{
    HANDLE_EXC_BEGIN
        return cgi_bin_path_.get();
    HANDLE_EXC_END
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
    saveTo_.set(saveTo);
}
RouteConfiguration::PathType& RouteConfiguration::getSaveTo(){
    HANDLE_EXC_BEGIN
        return saveTo_.get();
    HANDLE_EXC_END
}
const RouteConfiguration::PathType& RouteConfiguration::getSaveTo() const{
    HANDLE_EXC_BEGIN
        return saveTo_.get();
    HANDLE_EXC_END
}

bool RouteConfiguration::isDone() const{
    return isDone_;
}
void RouteConfiguration::done(){
    checkValidity_();
    isDone_ = true;
}

void RouteConfiguration::deleteData_(){
    isDone_ = false;
    methods_ = Wrapper<MethodsContainerType>();
    redirection_ = Wrapper<PathType>();
    directory_ = Wrapper<PathType>();
    directory_listening_ = false;
    default_if_directory_response_path_ = Wrapper<PathType>();
    cgi_script_path_ = Wrapper<PathType>();
    cgi_bin_path_ = Wrapper<PathType>();
    saveFiles_ = false;
    saveTo_ = Wrapper<PathType>();
}
void RouteConfiguration::copyData_(const RouteConfiguration& other){
    isDone_ = other.isDone_;
    methods_ = other.methods_;
    redirection_ = other.redirection_;
    directory_ = other.directory_;
    directory_listening_ = other.directory_listening_;
    default_if_directory_response_path_ = other.default_if_directory_response_path_;
    cgi_script_path_ = other.cgi_script_path_;
    cgi_bin_path_ = other.cgi_bin_path_;
    saveFiles_ = other.saveFiles_;
    saveTo_ = other.saveTo_;
}
void RouteConfiguration::checkValidity_() const{
    if (!methods_.isSet() || !methods_.get().size()) throw ExceptionType("Server methods are not set up", EXC_ARGS);
    if (!redirection_.isSet()) throw ExceptionType("HTTP redirection is not set up", EXC_ARGS);
    if (!directory_.isSet()) throw ExceptionType("Server directory is not set up", EXC_ARGS);
    if (directory_listening_ && !default_if_directory_response_path_.isSet()) throw ExceptionType("ifDirectoryReplyPage is not set up", EXC_ARGS);
    if (saveFiles_ && !saveTo_.isSet()) throw ExceptionType("Path for uploading files is not set up", EXC_ARGS);
    if (cgi_script_path_.isSet() && !cgi_bin_path_.isSet()) throw ExceptionType("CGI bin is not set for CGI script", EXC_ARGS);
}
void RouteConfiguration::throwOnDone() const{
    if (isDone_) throw ExceptionType("Route is done. You cannot change it anymore.", EXC_ARGS);
}

}
