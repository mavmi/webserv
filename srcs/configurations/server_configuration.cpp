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
    port_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<PortType>();
    host_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<HostType>();
    serverName_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ServerNameType>();
    errorPages_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ErrorPagesContainerType>();
    bodySize_ = 0;
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

void ServerConfiguration::setPort(PortType port){
    throwOnDone_();
    port_.set(port);
}
ServerConfiguration::PortType& ServerConfiguration::getPort(){
    HANDLE_EXC_BEGIN
        return port_.get();
    HANDLE_EXC_END
}
const ServerConfiguration::PortType& ServerConfiguration::getPort() const{
    HANDLE_EXC_BEGIN
        return port_.get();
    HANDLE_EXC_END
}

void ServerConfiguration::setHost(const HostType& host){
    throwOnDone_();
    host_.set(host);
}
ServerConfiguration::HostType& ServerConfiguration::getHost(){
    HANDLE_EXC_BEGIN
        return host_.get();
    HANDLE_EXC_END
}
const ServerConfiguration::HostType& ServerConfiguration::getHost() const{
    HANDLE_EXC_BEGIN
        return host_.get();
    HANDLE_EXC_END
}

void ServerConfiguration::setServerName(const ServerNameType& serverName){
    throwOnDone_();
    serverName_.set(serverName);
}
ServerConfiguration::ServerNameType& ServerConfiguration::getServerName(){
    HANDLE_EXC_BEGIN
        return serverName_.get();
    HANDLE_EXC_END
}
const ServerConfiguration::ServerNameType& ServerConfiguration::getServerName() const{
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
void ServerConfiguration::setErrorPage(const ErrorPageType& errorPage, SizeType position){
    throwOnDone_();
    errorPages_.get().at(position) = errorPage;
}
ServerConfiguration::ErrorPageType& ServerConfiguration::getErrorPage(SizeType position){
    HANDLE_EXC_BEGIN
        return errorPages_.get().at(position);
    HANDLE_EXC_END
}
const ServerConfiguration::ErrorPageType& ServerConfiguration::getErrorPage(SizeType position) const{
    HANDLE_EXC_BEGIN
        return errorPages_.get().at(position);
    HANDLE_EXC_END
}
void ServerConfiguration::addErrorPage(const ErrorPageType& errorPage){
    throwOnDone_();
    if (!errorPages_.isSet()) errorPages_.set(ErrorPagesContainerType());
    errorPages_.get().push_back(errorPage);
}
ServerConfiguration::SizeType ServerConfiguration::getErrorPagesCount() const{
    HANDLE_EXC_BEGIN
        return errorPages_.get().size();
    HANDLE_EXC_END
}

void ServerConfiguration::setBodySize(BodySizeType bodySize){
    throwOnDone_();
    bodySize_ = bodySize;
}
ServerConfiguration::BodySizeType ServerConfiguration::getBodySize() const{
    return bodySize_;
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
void ServerConfiguration::setRoute(const RouteType& route, SizeType position){
    throwOnDone_();
    routes_.get().at(position) = route;
}
ServerConfiguration::RouteType& ServerConfiguration::getRoute(SizeType position){
    HANDLE_EXC_BEGIN
        return routes_.get().at(position);
    HANDLE_EXC_END
}
const ServerConfiguration::RouteType& ServerConfiguration::getRoute(SizeType position) const{
    HANDLE_EXC_BEGIN
        return routes_.get().at(position);
    HANDLE_EXC_END
}
void ServerConfiguration::addRoute(const RouteType& route){
    throwOnDone_();
    if (!routes_.isSet()) routes_.set(RoutesContainerType());
    routes_.get().push_back(route);
}
ServerConfiguration::SizeType ServerConfiguration::getRoutesCount() const{
    HANDLE_EXC_BEGIN
        return routes_.get().size();
    HANDLE_EXC_END
}

void ServerConfiguration::deleteData_(){
    isDone_ = false;
    port_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<PortType>();
    host_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<HostType>();
    serverName_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ServerNameType>();
    errorPages_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ErrorPagesContainerType>();
    bodySize_ = 0;
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