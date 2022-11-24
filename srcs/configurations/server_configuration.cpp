#include "../../include/configurations/server_configuration.hpp"

namespace configuration {

ServerConfiguration::ServerConfiguration(){
    isDone_ = false;
    port_ = Wrapper<PortType>();
    host_ = Wrapper<HostType>();
    serverName_ = Wrapper<ServerNameType>();
    errorPages_ = Wrapper<ErrorPagesContainerType>();
    bodySize_ = 0;
    routes_ = Wrapper<RoutesContainerType>();
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
void* ServerConfiguration::operator new(size_t size){
    return malloc(size);
}
void* ServerConfiguration::operator new(size_t size, const ServerConfiguration& other){
    ServerConfiguration* ptr = (ServerConfiguration*)malloc(size);
    *ptr = other;
    return ptr;
}
void* ServerConfiguration::operator new[](size_t size){
    return malloc(size);
}
void ServerConfiguration::operator delete(void* ptr){
    free(ptr);
}
void ServerConfiguration::operator delete[](void* ptr){
    free(ptr);
}

void ServerConfiguration::setPort(PortType port){
    throwOnDone();
    port_.set(port);
}
ServerConfiguration::PortType ServerConfiguration::getPort() const{
    try {
        return port_.get();
    } catch (WrapperException& e){
        throw ExceptionType(e.what());
    }
}

void ServerConfiguration::setHost(const HostType& host){
    throwOnDone();
    host_.set(host);
}
ServerConfiguration::HostType& ServerConfiguration::getHost(){
    try {
        return host_.get();
    } catch (WrapperException& e){
        throw ExceptionType(e.what());
    }
}
const ServerConfiguration::HostType& ServerConfiguration::getHost() const{
    try {
        return host_.get();
    } catch (WrapperException& e){
        throw ExceptionType(e.what());
    }
}

void ServerConfiguration::setServerName(const ServerNameType& serverName){
    throwOnDone();
    serverName_.set(serverName);
}
ServerConfiguration::ServerNameType& ServerConfiguration::getServerName(){
    try {
        return serverName_.get();
    } catch (WrapperException& e){
        throw ExceptionType(e.what());
    }
}
const ServerConfiguration::ServerNameType& ServerConfiguration::getServerName() const{
    try {
        return serverName_.get();
    } catch (WrapperException& e){
        throw ExceptionType(e.what());
    }
}

void ServerConfiguration::setErrorPages(const ErrorPagesContainerType& errorPages){
    throwOnDone();
    errorPages_.set(errorPages);
}
ServerConfiguration::ErrorPagesContainerType& ServerConfiguration::getErrorPages(){
    try {
        return errorPages_.get();
    } catch (WrapperException& e){
        throw ExceptionType(e.what());
    }
}
const ServerConfiguration::ErrorPagesContainerType& ServerConfiguration::getErrorPages() const{
    try {
        return errorPages_.get();
    } catch (WrapperException& e){
        throw ExceptionType(e.what());
    }
}
void ServerConfiguration::setErrorPage(const ErrorPageType& errorPage, SizeType position){
    throwOnDone();
    errorPages_.get().at(position) = errorPage;
}
ServerConfiguration::ErrorPageType& ServerConfiguration::getErrorPage(SizeType position){
    try {
        return errorPages_.get().at(position);
    } catch (WrapperException& e){
        throw ExceptionType(e.what());
    }
}
const ServerConfiguration::ErrorPageType& ServerConfiguration::getErrorPage(SizeType position) const{
    try {
        return errorPages_.get().at(position);
    } catch (WrapperException& e){
        throw ExceptionType(e.what());
    }
}
void ServerConfiguration::addErrorPage(const ErrorPageType& errorPage){
    throwOnDone();
    if (!errorPages_.isSet()) errorPages_.set(ErrorPagesContainerType());
    errorPages_.get().push_back(errorPage);
}
ServerConfiguration::SizeType ServerConfiguration::getErrorPagesCount() const{
    try {
        return errorPages_.get().size();
    } catch (WrapperException& e){
        throw ExceptionType(e.what());
    }
}

void ServerConfiguration::setBodySize(BodySizeType bodySize){
    throwOnDone();
    bodySize_ = bodySize;
}
ServerConfiguration::BodySizeType ServerConfiguration::getBodySize() const{
    return bodySize_;
}

void ServerConfiguration::setRoutes(const RoutesContainerType& routes){
    throwOnDone();
    routes_.set(routes);
}
ServerConfiguration::RoutesContainerType& ServerConfiguration::getRoutes(){
    try {
        return routes_.get();
    } catch (WrapperException& e){
        throw ExceptionType(e.what());
    }
}
const ServerConfiguration::RoutesContainerType& ServerConfiguration::getRoutes() const{
    try {
        return routes_.get();
    } catch (WrapperException& e){
        throw ExceptionType(e.what());
    }
}
void ServerConfiguration::setRoute(const RouteType& route, SizeType position){
    throwOnDone();
    routes_.get().at(position) = route;
}
ServerConfiguration::RouteType& ServerConfiguration::getRoute(SizeType position){
    try {
        return routes_.get().at(position);
    } catch (WrapperException& e){
        throw ExceptionType(e.what());
    }
}
const ServerConfiguration::RouteType& ServerConfiguration::getRoute(SizeType position) const{
    try {
        return routes_.get().at(position);
    } catch (WrapperException& e){
        throw ExceptionType(e.what());
    }
}
void ServerConfiguration::addRoute(const RouteType& route){
    throwOnDone();
    if (!routes_.isSet()) routes_.set(RoutesContainerType());
    routes_.get().push_back(route);
}
ServerConfiguration::SizeType ServerConfiguration::getRoutesCount() const{
    try {
        return routes_.get().size();
    } catch (WrapperException& e){
        throw ExceptionType(e.what());
    }
}

bool ServerConfiguration::isDone() const{
    return isDone_;
}
void ServerConfiguration::done(){
    checkValidity_();
    isDone_ = true;
}

void ServerConfiguration::deleteData_(){
    isDone_ = false;
    port_ = Wrapper<PortType>();
    host_ = Wrapper<HostType>();
    serverName_ = Wrapper<ServerNameType>();
    errorPages_ = Wrapper<ErrorPagesContainerType>();
    bodySize_ = 0;
    routes_ = Wrapper<RoutesContainerType>();
}
void ServerConfiguration::copyData_(const ServerConfiguration& other){
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
void ServerConfiguration::throwOnDone() const{
    if (isDone_) throw ExceptionType("Route is done. You cannot change it anymore.", EXC_ARGS);
}

}
