#pragma once

#include "utils.hpp"
#include "exceptions.hpp"
#include "server_configuration.hpp"

// TO DO:
// - comments and messages
// - config elem getter from main config class
// - tests with different files
// - remove code duplicates (I'm telling about numbers parsing)

// This class contains all info from
// configuration file
class Configuration{
public:
    typedef ServerConfiguration SERVER_TYPE;

    Configuration();
    Configuration(const Configuration& other);
    ~Configuration();

    Configuration& operator=(const Configuration& other);

    // Parse configuration file.
    // May throw exception on error.
    void parseFile(const std::string& inputFile);

private:
    std::vector<SERVER_TYPE> servers_;

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
    HTTP_METHOD stringToHttpMethod(const std::string& str);
    std::set<std::string> stringToArray(const std::string& str);
    bool stringToBool(const std::string& str) const;
    template <typename ReturnType>
    ReturnType stringToNumber(const std::string& str) const {
        std::string errorMsg = "Bad number string";
        if (!str.size()) throw ConfigurationException(errorMsg, __FILE__, __FUNCTION__, __LINE__);

        ReturnType prev = 0, res = 0;
        for (size_t i = 0; i < str.size(); i++){
            char c = str.at(i);

            if (c < '0' || c > '9') throw ConfigurationException(errorMsg, __FILE__, __FUNCTION__, __LINE__);
            res = res * 10 + (c - '0');
            if (res < prev) throw ConfigurationException("Numeric value too long", __FILE__, __FUNCTION__, __LINE__);
            prev = res;
        }

        return static_cast<ReturnType>(res);
    }
    std::pair<std::string, std::string> split_(const std::string& str) const;
    void parseValueString_(const std::string& str);

};
