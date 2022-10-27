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

void ServerConfiguration::setPort(PORT_TYPE port){
    if (!port_) port_ = new PORT_TYPE(port);
    else *port_ = port;
}
ServerConfiguration::PORT_TYPE ServerConfiguration::getPort() const{
    if (port_) return *port_;
    throw ServerException("Port is not defined", __FILE__, __FUNCTION__, __LINE__);
}

void ServerConfiguration::setHost(const HOST_TYPE& host){
    if (!host_) host_ = new HOST_TYPE(host);
    else *host_ = host;
}
ServerConfiguration::HOST_TYPE& ServerConfiguration::getHost() const{
    if (host_) return *host_;
    throw ServerException("Host is not defined", __FILE__, __FUNCTION__, __LINE__);
}

void ServerConfiguration::setServerName(const SERVER_NAME_TYPE& serverName){
    if (!serverName_) serverName_ = new SERVER_NAME_TYPE(serverName);
    else *serverName_ = serverName; 
}
ServerConfiguration::SERVER_NAME_TYPE& ServerConfiguration::getServerName() const{
    if (serverName_) return *serverName_;
    throw ServerException("Server name is not defined", __FILE__, __FUNCTION__, __LINE__);
}

void ServerConfiguration::setErrorPages(const ERROR_PAGES_CONTAINER_TYPE& errorPages){
    if (!errorPages_) errorPages_ = new ERROR_PAGES_CONTAINER_TYPE(errorPages);
    else *errorPages_ = errorPages;
}
ServerConfiguration::ERROR_PAGES_CONTAINER_TYPE& ServerConfiguration::getErrorPages() const{
    if (errorPages_) return *errorPages_;
    throw ServerException("Error pages are not defined", __FILE__, __FUNCTION__, __LINE__);
}
void ServerConfiguration::setErrorPage(const ERROR_PAGE_TYPE& errorPage, SIZE_TYPE position){
    if (errorPages_) errorPages_->at(position) = errorPage;
    else throw ServerException("Error pages are not defined", __FILE__, __FUNCTION__, __LINE__);
}
ServerConfiguration::ERROR_PAGE_TYPE& ServerConfiguration::getErrorPage(SIZE_TYPE position){
    if (errorPages_) return errorPages_->at(position);
    else throw ServerException("Error pages are not defined", __FILE__, __FUNCTION__, __LINE__);
}
void ServerConfiguration::addErrorPage(const ERROR_PAGE_TYPE& errorPage){
    if (!errorPages_) errorPages_ = new  ERROR_PAGES_CONTAINER_TYPE();
    errorPages_->push_back(errorPage);        
}
ServerConfiguration::SIZE_TYPE ServerConfiguration::getErrorPagesCount() const{
    if (errorPages_) return errorPages_->size();
    else throw ServerException("Error pages are not defined", __FILE__, __FUNCTION__, __LINE__);
}

void ServerConfiguration::setBodySize(BODY_SIZE_TYPE bodySize){
    bodySize_ = bodySize;
}
ServerConfiguration::BODY_SIZE_TYPE ServerConfiguration::getBodySize() const{
    return bodySize_;
}

void ServerConfiguration::setRoutes(const ROUTES_CONTAINER_TYPE& routes){
    if (!routes_) routes_ = new ROUTES_CONTAINER_TYPE(routes);
    else *routes_ = routes;
}
ServerConfiguration::ROUTES_CONTAINER_TYPE& ServerConfiguration::getRoutes() const{
    if (routes_) return *routes_;
    throw ServerException("Routes are not defined", __FILE__, __FUNCTION__, __LINE__);
}
void ServerConfiguration::setRoute(const ROUTE_TYPE& route, SIZE_TYPE position){
    if (routes_) routes_->at(position) = route;
    throw ServerException("Routes are not defined", __FILE__, __FUNCTION__, __LINE__);
}
ServerConfiguration::ROUTE_TYPE& ServerConfiguration::getRoute(SIZE_TYPE position) const{
    if (routes_) return routes_->at(position);
    throw ServerException("Routes are not defined", __FILE__, __FUNCTION__, __LINE__);
}
void ServerConfiguration::addRoute(const ROUTE_TYPE& route){
    if (!routes_) routes_ = new ROUTES_CONTAINER_TYPE();
    routes_->push_back(route);
}
ServerConfiguration::SIZE_TYPE ServerConfiguration::getRoutesCount() const{
    if (routes_) return routes_->size();
    throw ServerException("Routes are not defined", __FILE__, __FUNCTION__, __LINE__);
}

bool ServerConfiguration::isDone() const{
    return isDone_;
}
void ServerConfiguration::done(){
    isDone_ = true;
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
    port_ = (other.port_) ? new PORT_TYPE(*other.port_) : NULL;
    host_ = (other.host_) ? new HOST_TYPE(*other.host_) : NULL;
    serverName_ = (other.serverName_) ? new SERVER_NAME_TYPE(*other.serverName_) : NULL;
    errorPages_ = (other.errorPages_) ? new ERROR_PAGES_CONTAINER_TYPE(*other.errorPages_) : NULL;
    bodySize_ = other.bodySize_;
    routes_ = (other.routes_) ? new ROUTES_CONTAINER_TYPE(*other.routes_) : NULL;
}

}
