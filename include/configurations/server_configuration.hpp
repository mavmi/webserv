#pragma once

#include "utils.hpp"
#include "exceptions.hpp"
#include "configuration_host.hpp"
#include "route_configuration.hpp"

// Contains information about server.
// Any getter may throw ServerException if it's value is not set.
// Use methods [isDone()] to check if the server is finished or not.
// Method [done()] marks the server as finished.
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

    ServerConfiguration();
    ServerConfiguration(const ServerConfiguration& other);
    ~ServerConfiguration();

    ServerConfiguration& operator=(const ServerConfiguration& other);

    void setPort(PORT_TYPE port);
    PORT_TYPE getPort() const;

    void setHost(const HOST_TYPE& host);
    HOST_TYPE& getHost() const;

    void setServerName(const SERVER_NAME_TYPE& serverName);
    SERVER_NAME_TYPE& getServerName() const;

    void setErrorPages(const ERROR_PAGES_CONTAINER_TYPE& errorPages);
    ERROR_PAGES_CONTAINER_TYPE& getErrorPages() const;
    void setErrorPage(const ERROR_PAGE_TYPE& errorPage, SIZE_TYPE position);
    ERROR_PAGE_TYPE& getErrorPage(SIZE_TYPE position);
    void addErrorPage(const ERROR_PAGE_TYPE& errorPage);
    SIZE_TYPE getErrorPagesCount() const;

    void setBodySize(BODY_SIZE_TYPE bodySize);
    BODY_SIZE_TYPE getBodySizse() const;

    void setRoutes(const ROUTES_CONTAINER_TYPE& routes);
    ROUTES_CONTAINER_TYPE& getRoutes() const;
    void setRoute(const ROUTE_TYPE& route, SIZE_TYPE position);
    ROUTE_TYPE& getRoute(SIZE_TYPE position) const;
    void addRoute(const ROUTE_TYPE& route);
    SIZE_TYPE getRoutesCount() const;

    bool isDone() const;
    void done();

private:
    bool isDone_;
    PORT_TYPE* port_;
    HOST_TYPE* host_;
    SERVER_NAME_TYPE* serverName_;
    ERROR_PAGES_CONTAINER_TYPE* errorPages_;
    BODY_SIZE_TYPE bodySize_;
    ROUTES_CONTAINER_TYPE* routes_;

    void deleteData_();
    void copyData_(const ServerConfiguration& other);

};
