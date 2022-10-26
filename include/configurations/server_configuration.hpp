#pragma once

#include "utils.hpp"
#include "exceptions.hpp"
#include "configuration_host.hpp"
#include "route_configuration.hpp"

class ServerConfiguration{
public:
    typedef size_t                          SIZE_TYPE;
    typedef unsigned short                  PORT_TYPE;
    typedef ConfigurationHost               HOST_TYPE;
    typedef std::string                     SERVER_NAME_TYPE;
    typedef std::string                     ERROR_PAGE_TYPE;
    typedef std::vector<ERROR_PAGE_TYPE>    ERROR_PAGES_CONTAINER_TYPE;
    typedef SIZE_TYPE                       BODY_SIZE_TYPE;
    typedef RouteConfiguration              ROUTE_TYPE;
    typedef std::vector<ROUTE_TYPE>         ROUTES_CONTAINER_TYPE;

    ServerConfiguration(){
        isDone_ = false;
        port_ = NULL;
        host_ = NULL;
        serverName_ = NULL;
        errorPages_ = NULL;
        bodySize_ = 0;
        routes_ = NULL;
    }
    ServerConfiguration(const ServerConfiguration& other){
        isDone_ = other.isDone_;
        port_ = (other.port_) ? new PORT_TYPE(*other.port_) : NULL;
        host_ = (other.host_) ? new HOST_TYPE(*other.host_) : NULL;
        serverName_ = (other.serverName_) ? new SERVER_NAME_TYPE(*other.serverName_) : NULL;
        errorPages_ = (other.errorPages_) ? new ERROR_PAGES_CONTAINER_TYPE(*other.errorPages_) : NULL;
        bodySize_ = other.bodySize_;
        routes_ = (other.routes_) ? new ROUTES_CONTAINER_TYPE(*other.routes_) : NULL;
    }
    ~ServerConfiguration(){
        deleteData_();
    }

    ServerConfiguration& operator=(const ServerConfiguration& other){
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

    void setPort(PORT_TYPE port){
        if (!port_) port_ = new PORT_TYPE(port);
        else *port_ = port;
    }
    PORT_TYPE getPort() const{
        if (port_) return *port_;
        throw ServerException("Port is not defined", __FILE__, __FUNCTION__, __LINE__);
    }

    void setHost(const HOST_TYPE& host){
        if (!host_) host_ = new HOST_TYPE(host);
        else *host_ = host;
    }
    HOST_TYPE& getHost() const{
        if (host_) return *host_;
        throw ServerException("Host is not defined", __FILE__, __FUNCTION__, __LINE__);
    }

    void setServerName(const SERVER_NAME_TYPE& serverName){
        if (!serverName_) serverName_ = new SERVER_NAME_TYPE(serverName);
        else *serverName_ = serverName; 
    }
    SERVER_NAME_TYPE& getServerName() const{
        if (serverName_) return *serverName_;
        throw ServerException("Server name is not defined", __FILE__, __FUNCTION__, __LINE__);
    }

    void setErrorPages(const ERROR_PAGES_CONTAINER_TYPE& errorPages){
        if (!errorPages_) errorPages_ = new ERROR_PAGES_CONTAINER_TYPE(errorPages);
        else *errorPages_ = errorPages;
    }
    ERROR_PAGES_CONTAINER_TYPE& getErrorPages() const{
        if (errorPages_) return *errorPages_;
        throw ServerException("Error pages are not defined", __FILE__, __FUNCTION__, __LINE__);
    }
    void setErrorPage(const ERROR_PAGE_TYPE& errorPage, SIZE_TYPE position){
        if (errorPages_) errorPages_->at(position) = errorPage;
        else throw ServerException("Error pages are not defined", __FILE__, __FUNCTION__, __LINE__);
    }
    ERROR_PAGE_TYPE& getErrorPage(SIZE_TYPE position){
        if (errorPages_) return errorPages_->at(position);
        else throw ServerException("Error pages are not defined", __FILE__, __FUNCTION__, __LINE__);
    }
    void addErrorPage(const ERROR_PAGE_TYPE& errorPage){
        if (!errorPages_) errorPages_ = new  ERROR_PAGES_CONTAINER_TYPE();
        errorPages_->push_back(errorPage);        
    }
    SIZE_TYPE getErrorPagesCount() const{
        if (errorPages_) return errorPages_->size();
        else throw ServerException("Error pages are not defined", __FILE__, __FUNCTION__, __LINE__);
    }

    void setBodySize(BODY_SIZE_TYPE bodySize){
        bodySize_ = bodySize;
    }
    BODY_SIZE_TYPE getBodySizse() const{
        return bodySize_;
    }

    void setRoutes(const ROUTES_CONTAINER_TYPE& routes){
        if (!routes_) routes_ = new ROUTES_CONTAINER_TYPE(routes);
        else *routes_ = routes;
    }
    ROUTES_CONTAINER_TYPE& getRoutes() const{
        if (routes_) return *routes_;
        throw ServerException("Routes are not defined", __FILE__, __FUNCTION__, __LINE__);
    }
    void setRoute(const ROUTE_TYPE& route, SIZE_TYPE position){
        if (routes_) routes_->at(position) = route;
        throw ServerException("Routes are not defined", __FILE__, __FUNCTION__, __LINE__);
    }
    ROUTE_TYPE& getRoute(SIZE_TYPE position) const{
        if (routes_) return routes_->at(position);
        throw ServerException("Routes are not defined", __FILE__, __FUNCTION__, __LINE__);
    }
    void addRoute(const ROUTE_TYPE& route){
        if (!routes_) routes_ = new ROUTES_CONTAINER_TYPE();
        routes_->push_back(route);
    }
    SIZE_TYPE getRoutesCount() const{
        if (routes_) return routes_->size();
        throw ServerException("Routes are not defined", __FILE__, __FUNCTION__, __LINE__);
    }

    bool isDone() const{
        return isDone_;
    }
    void done(){
        isDone_ = true;
    }

private:
    bool isDone_;
    PORT_TYPE* port_;
    HOST_TYPE* host_;
    SERVER_NAME_TYPE* serverName_;
    ERROR_PAGES_CONTAINER_TYPE* errorPages_;
    BODY_SIZE_TYPE bodySize_;
    ROUTES_CONTAINER_TYPE* routes_;

    void deleteData_(){
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

};
