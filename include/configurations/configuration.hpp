#pragma once

#include "utils.hpp"
#include "container.hpp"
#include "exceptions.hpp"
#include "server_configuration.hpp"

namespace configuration {

// This class contains all info from
// configuration file
class Configuration{
public:
    typedef ServerConfiguration     SERVER_TYPE;
    typedef Container<SERVER_TYPE>  SERVERS_CONTAINER_TYPE;

    Configuration();
    Configuration(const Configuration& other);
    ~Configuration();

    Configuration& operator=(const Configuration& other);

    // Parse configuration file.
    // May throw exception on error.
    void parseFile(const std::string& inputFile);
    SERVERS_CONTAINER_TYPE& getServers();

private:
    SERVERS_CONTAINER_TYPE servers_;

    // Check if string contains only whitespaces
    bool isLineEmpty_(const std::string& line) const;

    // Return reference to the last server in the list of servers.
    // Throw an exception if there are no servers.
    SERVER_TYPE& getLastServer_();
    // Return reference to the last route of last server.
    // May throw exception too.
    SERVER_TYPE::ROUTE_TYPE& getLastRoute_();

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
            throw ConfigurationException(e.what(), __FILE__, __FUNCTION__, __LINE__);
        }
    }
    std::pair<std::string, std::string> split_(const std::string& str) const;
    void parseValueString_(const std::string& str);

};

}
