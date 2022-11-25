#pragma once

#include "utils.hpp"
#include "container.hpp"
#include "exceptions.hpp"
#include "server_configuration.hpp"

namespace configuration {

// This class contains all info from
// configuration file
class Configuration{
friend Parser;
public:
    typedef ServerConfiguration                                                                 ServerType;
    typedef Container<ServerType>                                                               ServersContainerType;
    typedef ConfigurationException                                                              ExceptionType;
    typedef std::pair<const ServerType::HostType, const ServerType::PortType>                   HostPortPairType;
    typedef std::set<HostPortPairType>                                                          HostPortPairsContainerType;

    ~Configuration();

    // Parse configuration file.
    // May throw exception on error.
    void parseFile(const std::string& inputFile);
    ServersContainerType& getServers();
    const ServersContainerType& getServers() const;
    
    const ServerType& getServer(ServerType::PortType port) const;
    const ServerType& getServer(const ServerType::HostType& host) const;
    const ServerType& getServer(ServerType::PortType port, const ServerType::HostType& host) const;

    const HostPortPairsContainerType& getHostPortPairs() const;

private:
    ServersContainerType servers_;
    HostPortPairsContainerType hostPortPairs_;

    explicit Configuration();
    explicit Configuration(const Configuration& other);

    Configuration& operator=(const Configuration& other);

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
    HTTP_METHOD stringToHttpMethod_(const std::string& str);
    std::set<std::string> stringToArray_(const std::string& str);
    bool stringToBool_(const std::string& str) const;
    template <typename ReturnType>
    ReturnType stringToNumber_(const std::string& str) const {
        try {
            return utilsStringToNum<ReturnType>(str);
        } catch (UtilsException& e) {
            throw ExceptionType(e.what(), EXC_ARGS);
        }
    }
    std::pair<std::string, std::string> split_(const std::string& str) const;
    void parseValueString_(const std::string& str);
    void copyData_(const Configuration& other);
    void deleteData_();

};

}
