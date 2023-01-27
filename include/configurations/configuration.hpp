#pragma once

#include "utils.hpp"
#include "server_configuration.hpp"


namespace MAIN_NAMESPACE{
namespace CONFIG_NAMESPACE{

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
    typedef ServerConfiguration                                                                 ServerType;
    typedef MAIN_NAMESPACE::UTILS_NAMESPACE::Container<ServerType>                              ServersContainerType;
    typedef ConfigurationException                                                              ExceptionType;
    typedef std::pair<ServerType::HostType, ServerType::PortType>                               HostPortPairType;
    typedef std::set<HostPortPairType>                                                          HostPortPairsContainerType;
    typedef MAIN_NAMESPACE::UTILS_NAMESPACE::METHOD                                             MethodType;

    explicit Configuration();
    explicit Configuration(const Configuration& other);
    ~Configuration();

    Configuration& operator=(const Configuration& other);

    // Parse configuration file.
    // May throw exception on error.
    void parseFile(const std::string& inputFile);
    ServersContainerType& getServers();
    const ServersContainerType& getServers() const;
    
    const ServerType& getServer(ServerType::PortType port) const;
    const ServerType& getServer(const ServerType::HostType& host) const;
    const ServerType& getServer(ServerType::PortType port, const ServerType::HostType& host) const;

    ServersContainerType::SizeType getServersCount() const;
    const HostPortPairsContainerType& getHostPortPairs() const;

private:
    ServersContainerType servers_;
    HostPortPairsContainerType hostPortPairs_;

    // Check if string contains only whitespaces
    bool isLineEmpty_(const std::string& line) const;

    // Return reference to the last server in the list of servers.
    // Throw an exception if there are no servers.
    ServerType& getLastServer_();
    // Return reference to the last route of last server.
    // May throw exception too.
    ServerType::RouteType& getLastRoute_();

    /*
        All these methods below are about parsing different types
        of strings from an input file.
    */
    MethodType stringToHttpMethod_(const std::string& str);
    std::set<std::string> stringToArray_(const std::string& str);
    bool stringToBool_(const std::string& str) const;
    template <typename ReturnType>
    ReturnType stringToNumber_(const std::string& str) const {
        try {
            return MAIN_NAMESPACE::UTILS_NAMESPACE::utilsStringToNum<ReturnType>(str);
        } catch (MAIN_NAMESPACE::UTILS_NAMESPACE::UtilsException& e) {
            throw ExceptionType(e.what(), EXC_ARGS);
        }
    }
    std::pair<std::string, std::string> split_(const std::string& str) const;
    void parseValueString_(const std::string& str);
    void copyData_(const Configuration& other);
    void deleteData_();

};

}
}
