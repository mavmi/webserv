#include "../../includes/configurations/server_configuration.hpp"

namespace MAIN_NAMESPACE{
namespace CONFIG_NAMESPACE{
ServerException::ServerException(const char* msg) : Exception(msg){}
ServerException::ServerException(const std::string& msg) : Exception(msg){}
ServerException::ServerException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
ServerException::ServerException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
ServerException::ServerException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
ServerException::ServerException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string ServerException::output_() const {
    return "SERVER_EXCEPTION: " + msg_;
}
}
}


namespace MAIN_NAMESPACE{
namespace CONFIG_NAMESPACE{
ServerConfiguration::ServerConfiguration(){
    isDone_ = false;
    port_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ConfigurationPort>();
    host_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ConfigurationHost>();
    serverName_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    errorPages_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ErrorPagesContainerType>();
    bodySize_ = 0;
    root_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    routes_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<RoutesContainerType>();
}
ServerConfiguration::ServerConfiguration(const ServerConfiguration& other){
    copyData_(other);
}
ServerConfiguration::~ServerConfiguration(){
    deleteData_();
}

ServerConfiguration& ServerConfiguration::operator=(const ServerConfiguration& other){
    deleteData_();
    copyData_(other);
    return *this;
}

void ServerConfiguration::setPort(ConfigurationPort port){
    throwOnDone_();
    port_.set(port);
}
ConfigurationPort& ServerConfiguration::getPort(){
    HANDLE_EXC_BEGIN
        return port_.get();
    HANDLE_EXC_END
}
const ConfigurationPort& ServerConfiguration::getPort() const{
    HANDLE_EXC_BEGIN
        return port_.get();
    HANDLE_EXC_END
}

void ServerConfiguration::setHost(const ConfigurationHost& host){
    throwOnDone_();
    host_.set(host);
}
ConfigurationHost& ServerConfiguration::getHost(){
    HANDLE_EXC_BEGIN
        return host_.get();
    HANDLE_EXC_END
}
const ConfigurationHost& ServerConfiguration::getHost() const{
    HANDLE_EXC_BEGIN
        return host_.get();
    HANDLE_EXC_END
}

void ServerConfiguration::setServerName(const std::string& serverName){
    throwOnDone_();
    serverName_.set(serverName);
}
std::string& ServerConfiguration::getServerName(){
    HANDLE_EXC_BEGIN
        return serverName_.get();
    HANDLE_EXC_END
}
const std::string& ServerConfiguration::getServerName() const{
    HANDLE_EXC_BEGIN
        return serverName_.get();
    HANDLE_EXC_END
}

void ServerConfiguration::setErrorPages(const ErrorPagesContainerType& errorPages){
    throwOnDone_();
    errorPages_.set(errorPages);
}
ServerConfiguration::ErrorPagesContainerType& ServerConfiguration::getErrorPages(){
    HANDLE_EXC_BEGIN
        return errorPages_.get();
    HANDLE_EXC_END
}
const ServerConfiguration::ErrorPagesContainerType& ServerConfiguration::getErrorPages() const{
    HANDLE_EXC_BEGIN
        return errorPages_.get();
    HANDLE_EXC_END
}
void ServerConfiguration::setErrorPage(const std::string& errorPage, size_t position){
    throwOnDone_();
    errorPages_.get().at(position) = errorPage;
}
std::string& ServerConfiguration::getErrorPage(size_t position){
    HANDLE_EXC_BEGIN
        return errorPages_.get().at(position);
    HANDLE_EXC_END
}
const std::string& ServerConfiguration::getErrorPage(size_t position) const{
    HANDLE_EXC_BEGIN
        return errorPages_.get().at(position);
    HANDLE_EXC_END
}
void ServerConfiguration::addErrorPage(const std::string& errorPage){
    throwOnDone_();
    if (!errorPages_.isSet()) errorPages_.set(ErrorPagesContainerType());
    errorPages_.get().push_back(errorPage);
}
size_t ServerConfiguration::getErrorPagesCount() const{
    HANDLE_EXC_BEGIN
        return errorPages_.get().size();
    HANDLE_EXC_END
}

void ServerConfiguration::setBodySize(size_t bodySize){
    throwOnDone_();
    bodySize_ = bodySize;
}
size_t ServerConfiguration::getBodySize() const{
    return bodySize_;
}

void ServerConfiguration::setRoot(const std::string& root){
    throwOnDone_();
    root_.set(root);
}
std::string& ServerConfiguration::getRoot(){
    HANDLE_EXC_BEGIN
        return root_.get();
    HANDLE_EXC_END
}
const std::string& ServerConfiguration::getRoot() const{
    HANDLE_EXC_BEGIN
        return root_.get();
    HANDLE_EXC_END
}

void ServerConfiguration::setRoutes(const RoutesContainerType& routes){
    throwOnDone_();
    routes_.set(routes);
}
ServerConfiguration::RoutesContainerType& ServerConfiguration::getRoutes(){
    HANDLE_EXC_BEGIN
        return routes_.get();
    HANDLE_EXC_END
}
const ServerConfiguration::RoutesContainerType& ServerConfiguration::getRoutes() const{
    HANDLE_EXC_BEGIN
        return routes_.get();
    HANDLE_EXC_END
}
void ServerConfiguration::setRoute(const RouteConfiguration& route, size_t position){
    throwOnDone_();
    routes_.get().at(position) = route;
}
RouteConfiguration& ServerConfiguration::getRoute(size_t position){
    HANDLE_EXC_BEGIN
        return routes_.get().at(position);
    HANDLE_EXC_END
}
const RouteConfiguration& ServerConfiguration::getRoute(size_t position) const{
    HANDLE_EXC_BEGIN
        return routes_.get().at(position);
    HANDLE_EXC_END
}
RouteConfiguration& ServerConfiguration::getRoute(const std::string& url){
    HANDLE_EXC_BEGIN
    for (RoutesContainerType::SizeType i = 0; i < routes_.get().size(); i++){
        RouteConfiguration& route = routes_.get().at(i);
        if (route.getRedirection() == url) return route;
    }
    throw ExceptionType("Route with such url not found: " + url);
    HANDLE_EXC_END
}
const RouteConfiguration& ServerConfiguration::getRoute(const std::string& url) const{
    HANDLE_EXC_BEGIN
    for (RoutesContainerType::SizeType i = 0; i < routes_.get().size(); i++){
        const RouteConfiguration& route = routes_.get().at(i);
        if (route.getRedirection() == url) return route;
    }
    throw ExceptionType("Route with such url not found: " + url);
    HANDLE_EXC_END
}
void ServerConfiguration::addRoute(const RouteConfiguration& route){
    throwOnDone_();
    if (!routes_.isSet()) routes_.set(RoutesContainerType());
    routes_.get().push_back(route);
}
size_t ServerConfiguration::getRoutesCount() const{
    HANDLE_EXC_BEGIN
        return routes_.get().size();
    HANDLE_EXC_END
}

void ServerConfiguration::deleteData_(){
    isDone_ = false;
    port_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ConfigurationPort>();
    host_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ConfigurationHost>();
    serverName_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    errorPages_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ErrorPagesContainerType>();
    bodySize_ = 0;
    root_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    routes_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<RoutesContainerType>();
}
void ServerConfiguration::copyData_(const MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent& o){
    const ServerConfiguration& other = dynamic_cast<const ServerConfiguration&>(o);

    isDone_ = other.isDone_;
    port_ = other.port_;
    host_ = other.host_;
    serverName_ = other.serverName_;
    errorPages_ = other.errorPages_;
    bodySize_ = other.bodySize_;
    root_ = other.root_;
    routes_ = other.routes_;
}
void ServerConfiguration::checkValidity_() const{
    if (!port_.isSet()) throw ExceptionType("Port is not set up", EXC_ARGS);
    if (!host_.isSet()) throw ExceptionType("Host is not set up", EXC_ARGS);
    if (!errorPages_.isSet() || !errorPages_.get().size()) throw ExceptionType("Error pages are not set up", EXC_ARGS);
    if (!bodySize_) throw ExceptionType("Body size is not set up", EXC_ARGS);
}
void ServerConfiguration::throwOnDone_() const{
    if (isDone_) throw ExceptionType("Route is done. You cannot change it anymore.", EXC_ARGS);
}

}
}