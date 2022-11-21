#include "../../include/configurations/server_configuration.hpp"

namespace configuration {

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
    throwOnDone();
    if (!port_) port_ = new PortType(port);
    else *port_ = port;
}
ServerConfiguration::PortType ServerConfiguration::getPort() const{
    if (port_) return *port_;
    throw ExceptionType("Port is not defined", __FILE__, __FUNCTION__, __LINE__);
}

void ServerConfiguration::setHost(const HostType& host){
    throwOnDone();
    if (!host_) host_ = new HostType(host);
    else *host_ = host;
}
ServerConfiguration::HostType& ServerConfiguration::getHost(){
    if (host_) return *host_;
    throw ExceptionType("Host is not defined", __FILE__, __FUNCTION__, __LINE__);
}
const ServerConfiguration::HostType& ServerConfiguration::getHost() const{
    if (host_) return *host_;
    throw ExceptionType("Host is not defined", __FILE__, __FUNCTION__, __LINE__);
}

void ServerConfiguration::setServerName(const ServerNameType& serverName){
    throwOnDone();
    if (!serverName_) serverName_ = new ServerNameType(serverName);
    else *serverName_ = serverName; 
}
ServerConfiguration::ServerNameType& ServerConfiguration::getServerName(){
    if (serverName_) return *serverName_;
    throw ExceptionType("Server name is not defined", __FILE__, __FUNCTION__, __LINE__);
}
const ServerConfiguration::ServerNameType& ServerConfiguration::getServerName() const{
    if (serverName_) return *serverName_;
    throw ExceptionType("Server name is not defined", __FILE__, __FUNCTION__, __LINE__);
}

void ServerConfiguration::setErrorPages(const ErrorPagesContainerType& errorPages){
    throwOnDone();
    if (!errorPages_) errorPages_ = new ErrorPagesContainerType(errorPages);
    else *errorPages_ = errorPages;
}
ServerConfiguration::ErrorPagesContainerType& ServerConfiguration::getErrorPages(){
    if (errorPages_) return *errorPages_;
    throw ExceptionType("Error pages are not defined", __FILE__, __FUNCTION__, __LINE__);
}
const ServerConfiguration::ErrorPagesContainerType& ServerConfiguration::getErrorPages() const{
    if (errorPages_) return *errorPages_;
    throw ExceptionType("Error pages are not defined", __FILE__, __FUNCTION__, __LINE__);
}
void ServerConfiguration::setErrorPage(const ErrorPageType& errorPage, SizeType position){
    throwOnDone();
    if (errorPages_) errorPages_->at(position) = errorPage;
    else throw ExceptionType("Error pages are not defined", __FILE__, __FUNCTION__, __LINE__);
}
ServerConfiguration::ErrorPageType& ServerConfiguration::getErrorPage(SizeType position){
    if (errorPages_) return errorPages_->at(position);
    else throw ExceptionType("Error pages are not defined", __FILE__, __FUNCTION__, __LINE__);
}
const ServerConfiguration::ErrorPageType& ServerConfiguration::getErrorPage(SizeType position) const{
    if (errorPages_) return errorPages_->at(position);
    else throw ExceptionType("Error pages are not defined", __FILE__, __FUNCTION__, __LINE__);
}
void ServerConfiguration::addErrorPage(const ErrorPageType& errorPage){
    throwOnDone();
    if (!errorPages_) errorPages_ = new  ErrorPagesContainerType();
    errorPages_->push_back(errorPage);        
}
ServerConfiguration::SizeType ServerConfiguration::getErrorPagesCount() const{
    if (errorPages_) return errorPages_->size();
    else throw ExceptionType("Error pages are not defined", __FILE__, __FUNCTION__, __LINE__);
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
    if (!routes_) routes_ = new RoutesContainerType(routes);
    else *routes_ = routes;
}
ServerConfiguration::RoutesContainerType& ServerConfiguration::getRoutes(){
    if (routes_) return *routes_;
    throw ExceptionType("Routes are not defined", __FILE__, __FUNCTION__, __LINE__);
}
const ServerConfiguration::RoutesContainerType& ServerConfiguration::getRoutes() const{
    if (routes_) return *routes_;
    throw ExceptionType("Routes are not defined", __FILE__, __FUNCTION__, __LINE__);
}
void ServerConfiguration::setRoute(const RouteType& route, SizeType position){
    throwOnDone();
    if (routes_) routes_->at(position) = route;
    throw ExceptionType("Routes are not defined", __FILE__, __FUNCTION__, __LINE__);
}
ServerConfiguration::RouteType& ServerConfiguration::getRoute(SizeType position){
    if (routes_) return routes_->at(position);
    throw ExceptionType("Routes are not defined", __FILE__, __FUNCTION__, __LINE__);
}
const ServerConfiguration::RouteType& ServerConfiguration::getRoute(SizeType position) const{
    if (routes_) return routes_->at(position);
    throw ExceptionType("Routes are not defined", __FILE__, __FUNCTION__, __LINE__);
}
void ServerConfiguration::addRoute(const RouteType& route){
    throwOnDone();
    if (!routes_) routes_ = new RoutesContainerType();
    routes_->push_back(route);
}
ServerConfiguration::SizeType ServerConfiguration::getRoutesCount() const{
    if (routes_) return routes_->size();
    throw ExceptionType("Routes are not defined", __FILE__, __FUNCTION__, __LINE__);
}

bool ServerConfiguration::isDone() const{
    return isDone_;
}
void ServerConfiguration::done(){
    checkValidity_();
    isDone_ = true;
}

ServerConfiguration* ServerConfiguration::getObject(){
    return new ServerConfiguration();
}
ServerConfiguration* ServerConfiguration::getObject(const ServerConfiguration& other){
    return new ServerConfiguration(other);
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
void ServerConfiguration::copyData_(const ServerConfiguration& other){
    isDone_ = other.isDone_;
    port_ = (other.port_) ? new PortType(*other.port_) : NULL;
    host_ = (other.host_) ? new HostType(*other.host_) : NULL;
    serverName_ = (other.serverName_) ? new ServerNameType(*other.serverName_) : NULL;
    errorPages_ = (other.errorPages_) ? new ErrorPagesContainerType(*other.errorPages_) : NULL;
    bodySize_ = other.bodySize_;
    routes_ = (other.routes_) ? new RoutesContainerType(*other.routes_) : NULL;
}
void ServerConfiguration::checkValidity_() const{
    if (!port_) throw ExceptionType("Port is not set up", __FILE__, __FUNCTION__, __LINE__);
    if (!host_) throw ExceptionType("Host is not set up", __FILE__, __FUNCTION__, __LINE__);
    if (!errorPages_ || !errorPages_->size()) throw ExceptionType("Error pages are not set up", __FILE__, __FUNCTION__, __LINE__);
    if (!bodySize_) throw ExceptionType("Body size is not set up", __FILE__, __FUNCTION__, __LINE__);
}
void ServerConfiguration::throwOnDone() const{
    if (isDone_) throw ExceptionType("Route is done. You cannot change it anymore.", __FILE__, __FUNCTION__, __LINE__);
}

}
