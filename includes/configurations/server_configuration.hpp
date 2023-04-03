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
    typedef MAIN_NAMESPACE::UTILS_NAMESPACE::Container<std::string>         ErrorPagesContainerType;
    typedef MAIN_NAMESPACE::UTILS_NAMESPACE::Container<RouteConfiguration>  RoutesContainerType;
    typedef ServerException                                                 ExceptionType;

    explicit ServerConfiguration();
    explicit ServerConfiguration(const ServerConfiguration& other);
    ~ServerConfiguration();

    ServerConfiguration& operator=(const ServerConfiguration& other);

    void setPort(ConfigurationPort port);
    ConfigurationPort& getPort();
    const ConfigurationPort& getPort() const;

    void setHost(const ConfigurationHost& host);
    ConfigurationHost& getHost();
    const ConfigurationHost& getHost() const;

    void setServerName(const std::string& serverName);
    std::string& getServerName();
    const std::string& getServerName() const;

    void setErrorPages(const ErrorPagesContainerType& errorPages);
    ErrorPagesContainerType& getErrorPages();
    const ErrorPagesContainerType& getErrorPages() const;
    void setErrorPage(const std::string& errorPage, size_t position);
    std::string& getErrorPage(size_t position);
    const std::string& getErrorPage(size_t position) const;
    void addErrorPage(const std::string& errorPage);
    size_t getErrorPagesCount() const;

    void setBodySize(size_t bodySize);
    size_t getBodySize() const;

    void setRoutes(const RoutesContainerType& routes);
    RoutesContainerType& getRoutes();
    const RoutesContainerType& getRoutes() const;
    void setRoute(const RouteConfiguration& route, size_t position);
    RouteConfiguration& getRoute(size_t position);
    const RouteConfiguration& getRoute(size_t position) const;
    RouteConfiguration& getRoute(const std::string& url);
    const RouteConfiguration& getRoute(const std::string& url) const;
    void addRoute(const RouteConfiguration& route);
    size_t getRoutesCount() const;

private:
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ConfigurationPort> port_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ConfigurationHost> host_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> serverName_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ErrorPagesContainerType> errorPages_;
    size_t bodySize_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<RoutesContainerType> routes_;
    
    void deleteData_();
    void copyData_(const MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent& o);
    void checkValidity_() const;
    void throwOnDone_() const;

};

}
}
