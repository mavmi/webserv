#include "../../includes/configurations/route_configuration.hpp"

namespace MAIN_NAMESPACE{
namespace CONFIG_NAMESPACE{
RouteException::RouteException(const char* msg) : Exception(msg){}
RouteException::RouteException(const std::string& msg) : Exception(msg){}
RouteException::RouteException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
RouteException::RouteException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
RouteException::RouteException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
RouteException::RouteException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string RouteException::output_() const {
    return "ROUTE_EXCEPTION: " + msg_;
}
}
}


namespace MAIN_NAMESPACE{
namespace CONFIG_NAMESPACE{
RouteConfiguration::RouteConfiguration(){
    isDone_ = false;
    methods_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<MethodsContainerType>();
    redirection_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    directory_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    directory_listening_ = false;
    default_if_directory_response_path_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    cgi_script_path_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    cgi_bin_path_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    saveFiles_ = false;
    saveTo_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
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
    throwOnDone_();
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
void RouteConfiguration::setMethod(const MethodType& method, size_t position){
    throwOnDone_();
    methods_.get().at(position) = method;
}
RouteConfiguration::MethodType& RouteConfiguration::getMethod(size_t position){
    HANDLE_EXC_BEGIN
        return methods_.get().at(position);
    HANDLE_EXC_END
}
const RouteConfiguration::MethodType& RouteConfiguration::getMethod(size_t position) const{
    HANDLE_EXC_BEGIN
        return methods_.get().at(position);
    HANDLE_EXC_END
}
void RouteConfiguration::addMethod(const MethodType& method){
    throwOnDone_();
    if (!methods_.isSet()) methods_.set(MethodsContainerType());
    methods_.get().push_back(method);
}
size_t RouteConfiguration::getMethodsCount() const{
    HANDLE_EXC_BEGIN
        return methods_.get().size();
    HANDLE_EXC_END
}
bool RouteConfiguration::isMethodPresent(UTILS_NAMESPACE::METHOD method) const {
    HANDLE_EXC_BEGIN
        for (MethodsContainerType::SizeType i = 0; i < methods_.get().size(); i++){
            if (methods_.get().at(i) == method) return true;
        }
        return false;
    HANDLE_EXC_END
}

void RouteConfiguration::setRedirection(const std::string& redirection){
    throwOnDone_();
    if (directory_.isSet() && directory_.get() == redirection){
        redirection_.set("*");
    } else {
        redirection_.set(redirection);
    }
}
std::string& RouteConfiguration::getRedirection(){
    HANDLE_EXC_BEGIN
        return redirection_.get();
    HANDLE_EXC_END
}
const std::string& RouteConfiguration::getRedirection() const{
    HANDLE_EXC_BEGIN
        return redirection_.get();
    HANDLE_EXC_END
}

void RouteConfiguration::setDirectory(const std::string& directory){
    throwOnDone_();
    if (redirection_.isSet() && redirection_.get() == directory){
        redirection_.set("*");
    }
    directory_.set(directory);
}
std::string& RouteConfiguration::getDirectory(){
    HANDLE_EXC_BEGIN
        return directory_.get();
    HANDLE_EXC_END
}
const std::string& RouteConfiguration::getDirectory() const{
    HANDLE_EXC_BEGIN
        return directory_.get();
    HANDLE_EXC_END
}

void RouteConfiguration::setDirectoryListening(bool directoryListening){
    throwOnDone_();
    directory_listening_ = directoryListening;
}
bool RouteConfiguration::getDirectoryListening() const{
    return directory_listening_;
}

void RouteConfiguration::setDefaultIfDirectoryResponse(const std::string& default_if_directory_response_path){
    throwOnDone_();
    default_if_directory_response_path_.set(default_if_directory_response_path);
}
std::string& RouteConfiguration::getDefaultIfDirectoryResponse(){
    HANDLE_EXC_BEGIN
        return default_if_directory_response_path_.get();
    HANDLE_EXC_END
}
const std::string& RouteConfiguration::getDefaultIfDirectoryResponse() const{
    HANDLE_EXC_BEGIN
        return default_if_directory_response_path_.get();
    HANDLE_EXC_END
}

void RouteConfiguration::setCgiScriptPath(const std::string& cgi_script_path){
    throwOnDone_();
    cgi_script_path_.set(cgi_script_path);
}
std::string& RouteConfiguration::getCgiScriptPath(){
    HANDLE_EXC_BEGIN
        return cgi_script_path_.get();
    HANDLE_EXC_END
}
const std::string& RouteConfiguration::getCgiScriptPath() const{
    HANDLE_EXC_BEGIN
        return cgi_script_path_.get();
    HANDLE_EXC_END
}

void RouteConfiguration::setCgiBinPath(const std::string& cgi_bin_path){
    throwOnDone_();
    cgi_bin_path_.set(cgi_bin_path);
}
std::string& RouteConfiguration::getCgiBinPath(){
    HANDLE_EXC_BEGIN
        return cgi_bin_path_.get();
    HANDLE_EXC_END
}
const std::string& RouteConfiguration::getCgiBinPath() const{
    HANDLE_EXC_BEGIN
        return cgi_bin_path_.get();
    HANDLE_EXC_END
}

void RouteConfiguration::setSaveFiles(bool saveFiles){
    throwOnDone_();
    saveFiles_ = saveFiles;
}
bool RouteConfiguration::getSaveFiles() const{
    return saveFiles_;
}

void RouteConfiguration::setSaveTo(const std::string& saveTo){
    throwOnDone_();
    saveTo_.set(saveTo);
}
std::string& RouteConfiguration::getSaveTo(){
    HANDLE_EXC_BEGIN
        return saveTo_.get();
    HANDLE_EXC_END
}
const std::string& RouteConfiguration::getSaveTo() const{
    HANDLE_EXC_BEGIN
        return saveTo_.get();
    HANDLE_EXC_END
}

void RouteConfiguration::deleteData_(){
    isDone_ = false;
    methods_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<MethodsContainerType>();
    redirection_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    directory_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    directory_listening_ = false;
    default_if_directory_response_path_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    cgi_script_path_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    cgi_bin_path_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    saveFiles_ = false;
    saveTo_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
}
void RouteConfiguration::copyData_(const MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent& o){
    const RouteConfiguration& other = dynamic_cast<const RouteConfiguration&>(o);
    
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
void RouteConfiguration::throwOnDone_() const{
    if (isDone_) throw ExceptionType("Route is done. You cannot change it anymore.", EXC_ARGS);
}

}
}
