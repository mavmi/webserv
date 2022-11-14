#pragma once

#include "utils.hpp"
#include "container.hpp"
#include "exceptions.hpp"
#include "configuration_host.hpp"
#include "route_configuration.hpp"

namespace configuration {

// Contains information about server.
// Any getter may throw ServerException if it's value is not set.
// Use methods [isDone()] to check if the server is finished or not.
// Method [done()] marks the server as finished. May throw an exception.
class ServerConfiguration{
public:
    typedef size_t                          SizeType;
    typedef uint16_t                        PortType;
    typedef ConfigurationHost               HostType;
    typedef std::string                     ServerNameType;
    typedef std::string                     ErrorPageType;
    typedef Container<ErrorPageType>        ErrorPagesContainerType;
    typedef SizeType                        BodySizeType;
    typedef RouteConfiguration              RouteType;
    typedef Container<RouteType>            RoutesContainerType;
    typedef ServerException                 ExceptionType;

    ServerConfiguration();
    ServerConfiguration(const ServerConfiguration& other);
    ~ServerConfiguration();

    ServerConfiguration& operator=(const ServerConfiguration& other);

    void setPort(PortType port);
    PortType getPort() const;

    void setHost(const HostType& host);
    HostType& getHost() const;

    void setServerName(const ServerNameType& serverName);
    ServerNameType& getServerName() const;

    void setErrorPages(const ErrorPagesContainerType& errorPages);
    ErrorPagesContainerType& getErrorPages() const;
    void setErrorPage(const ErrorPageType& errorPage, SizeType position);
    ErrorPageType& getErrorPage(SizeType position);
    void addErrorPage(const ErrorPageType& errorPage);
    SizeType getErrorPagesCount() const;

    void setBodySize(BodySizeType bodySize);
    BodySizeType getBodySize() const;

    void setRoutes(const RoutesContainerType& routes);
    RoutesContainerType& getRoutes() const;
    void setRoute(const RouteType& route, SizeType position);
    RouteType& getRoute(SizeType position) const;
    void addRoute(const RouteType& route);
    SizeType getRoutesCount() const;

    bool isDone() const;
    void done();

private:
    bool isDone_;
    PortType* port_;
    HostType* host_;
    ServerNameType* serverName_;
    ErrorPagesContainerType* errorPages_;
    BodySizeType bodySize_;
    RoutesContainerType* routes_;

    void deleteData_();
    void copyData_(const ServerConfiguration& other);
    void checkValidity_() const;
    void throwOnDone() const;

};

}
