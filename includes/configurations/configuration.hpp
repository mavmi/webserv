#pragma once

#include "utils.hpp"
#include "server_configuration.hpp"

namespace MAIN_NAMESPACE{

class ConfigurationException : public MAIN_NAMESPACE::UTILS_NAMESPACE::Exception {
public:
    ConfigurationException(const char* msg);
    ConfigurationException(const std::string& msg);

    ConfigurationException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    ConfigurationException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    ConfigurationException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    ConfigurationException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    virtual std::string output_() const;

};


// This class contains all info from
// configuration file
class Configuration{
public:
    typedef MAIN_NAMESPACE::CONFIG_NAMESPACE::ServerConfiguration                               ServerType;
    typedef MAIN_NAMESPACE::UTILS_NAMESPACE::Container<ServerType>                              ServersContainerType;
    typedef ConfigurationException                                                              ExceptionType;
    typedef std::pair<ServerType::HostType, ServerType::PortType>                               HostPortPairType;
    typedef std::set<HostPortPairType>                                                          HostPortPairsContainerType;
    typedef MAIN_NAMESPACE::UTILS_NAMESPACE::METHOD                                             MethodType;

    explicit Configuration();
    explicit Configuration(const Configuration& other);
    ~Configuration();

    Configuration& operator=(const Configuration& other);

    ServersContainerType::SizeType getServersCount() const;

    ServersContainerType& getServers();
    const ServersContainerType& getServers() const;

    HostPortPairsContainerType& getHostPortPairs();
    const HostPortPairsContainerType& getHostPortPairs() const;
    
    const ServerType& getServer(ServerType::PortType port) const;
    const ServerType& getServer(const ServerType::HostType& host) const;
    const ServerType& getServer(ServerType::PortType port, const ServerType::HostType& host) const;

private:
    ServersContainerType servers_;
    HostPortPairsContainerType hostPortPairs_;

    void copyData_(const Configuration& other);
    void deleteData_();

};

}
