#pragma once

#include "utils.hpp"
#include "configuration_port.hpp"
#include "configuration_host.hpp"
#include "route_configuration.hpp"

namespace MAIN_NAMESPACE{
namespace CONFIG_NAMESPACE{

class ServerException : public MAIN_NAMESPACE::UTILS_NAMESPACE::Exception {
public:
    ServerException(const char* msg);
    ServerException(const std::string& msg);

    ServerException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    ServerException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    ServerException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    ServerException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    std::string output_() const;

};

// Contains information about server.
// Any getter may throw ServerException if it's value is not set.
// Use methods [isDone()] to check if the server is finished or not.
// Method [done()] marks the server as finished. May throw an exception.
class ServerConfiguration : public MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent{
public:
    typedef size_t                                                          SizeType;
    typedef ConfigurationPort                                               PortType;
    typedef ConfigurationHost                                               HostType;
    typedef std::string                                                     ServerNameType;
    typedef std::string                                                     ErrorPageType;
    typedef MAIN_NAMESPACE::UTILS_NAMESPACE::Container<ErrorPageType>       ErrorPagesContainerType;
    typedef SizeType                                                        BodySizeType;
    typedef RouteConfiguration                                              RouteType;
    typedef MAIN_NAMESPACE::UTILS_NAMESPACE::Container<RouteType>           RoutesContainerType;
    typedef ServerException                                                 ExceptionType;

    explicit ServerConfiguration();
    explicit ServerConfiguration(const ServerConfiguration& other);
    ~ServerConfiguration();

    ServerConfiguration& operator=(const ServerConfiguration& other);

    void setPort(PortType port);
    PortType getPort() const;

    void setHost(const HostType& host);
    HostType& getHost();
    const HostType& getHost() const;

    void setServerName(const ServerNameType& serverName);
    ServerNameType& getServerName();
    const ServerNameType& getServerName() const;

    void setErrorPages(const ErrorPagesContainerType& errorPages);
    ErrorPagesContainerType& getErrorPages();
    const ErrorPagesContainerType& getErrorPages() const;
    void setErrorPage(const ErrorPageType& errorPage, SizeType position);
    ErrorPageType& getErrorPage(SizeType position);
    const ErrorPageType& getErrorPage(SizeType position) const;
    void addErrorPage(const ErrorPageType& errorPage);
    SizeType getErrorPagesCount() const;

    void setBodySize(BodySizeType bodySize);
    BodySizeType getBodySize() const;

    void setRoutes(const RoutesContainerType& routes);
    RoutesContainerType& getRoutes();
    const RoutesContainerType& getRoutes() const;
    void setRoute(const RouteType& route, SizeType position);
    RouteType& getRoute(SizeType position);
    const RouteType& getRoute(SizeType position) const;
    void addRoute(const RouteType& route);
    SizeType getRoutesCount() const;

private:
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<PortType> port_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<HostType> host_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ServerNameType> serverName_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ErrorPagesContainerType> errorPages_;
    BodySizeType bodySize_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<RoutesContainerType> routes_;
    
    void deleteData_();
    void copyData_(const MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent& o);
    void checkValidity_() const;
    void throwOnDone_() const;

};

}
}
