#pragma once

#include "utils.hpp"
#include "exceptions.hpp"
#include "server_configuration.hpp"

// TO DO:
// - split code
// - comments and messages
// - config elem getter from main config class
// - tests with different files
// - remove code duplicates (I'm telling about numbers parsing)

// This class contains all info from
// configuration file
class Configuration{
public:
    typedef ServerConfiguration SERVER_TYPE;

    Configuration(){

    }
    Configuration(const Configuration& other){
        operator=(other);
    }
    ~Configuration(){

    }

    Configuration& operator=(const Configuration& other){
        servers_ = other.servers_;
        return *this;
    }

    // Parse configuration file.
    // May throw exception on error.
    void parseFile(const std::string& inputFile){
        typedef std::string::iterator Iterator;

        const std::string errorMsg = "Configuration file parsing error";
        std::ifstream inputFileStream(inputFile.c_str(), std::ios::in);
        if (!inputFileStream.is_open()) throw ConfigurationException("Unable to open input file: " + inputFile, __FILE__, __FUNCTION__, __LINE__);

        std::string line;
        while(std::getline(inputFileStream, line)){     // it does not have whitespaces here anymore    
            if (isLineEmpty_(line)) continue;
            line.resize(std::distance(line.begin(), std::remove_if(line.begin(), line.end(), isspace)));    // Remove whitespaces from line

            Iterator iter = line.begin();
            while (iter != line.end()){
                char c = *iter;

                if (c == '{'){          // Start server

                    try {
                        SERVER_TYPE& lastServer = getLastServer_();
                        if (!lastServer.isDone()) throw Exception(errorMsg, __FILE__, __FUNCTION__, __LINE__);
                        servers_.push_back(SERVER_TYPE());
                    } catch (ConfigurationException&){
                        servers_.push_back(SERVER_TYPE());
                    } catch (Exception&){
                        throw;
                    }

                } else if (c == '}'){   // Finish server

                    try {
                        SERVER_TYPE& lastServer = getLastServer_();
                        if (lastServer.isDone()) throw Exception(errorMsg, __FILE__, __FUNCTION__, __LINE__);
                        if (!getLastRoute_().isDone()) throw Exception(errorMsg, __FILE__, __FUNCTION__, __LINE__);
                        lastServer.done();
                    } catch (ServerException&){
                        getLastServer_().done();
                    } catch (ConfigurationException&){
                        throw;
                    } catch (Exception&){
                        throw;
                    }

                } else if (c == '['){   // Start route for last server

                    try {
                        SERVER_TYPE& lastServer = getLastServer_();
                        if (lastServer.isDone()) throw Exception(errorMsg, __FILE__, __FUNCTION__, __LINE__);
                        if (!getLastRoute_().isDone()) throw Exception(errorMsg, __FILE__, __FUNCTION__, __LINE__);
                        lastServer.addRoute(SERVER_TYPE::ROUTE_TYPE());
                    } catch (ServerException&){
                        getLastServer_().addRoute(SERVER_TYPE::ROUTE_TYPE());
                    } catch (ConfigurationException&){
                        throw;
                    } catch (Exception&){
                        throw;
                    }

                } else if (c == ']'){   // Finish route for last server

                    try {
                        SERVER_TYPE& lastServer = getLastServer_();
                        if (lastServer.isDone()) throw Exception(errorMsg, __FILE__, __FUNCTION__, __LINE__);
                        if (getLastRoute_().isDone()) throw Exception(errorMsg, __FILE__, __FUNCTION__, __LINE__);
                        getLastRoute_().done();
                    } catch (ServerException&){
                        throw;
                    } catch (ConfigurationException&){
                        throw;
                    } catch (Exception&){
                        throw;
                    }

                } else {                // value string

                    Iterator begin = iter;
                    Iterator end = std::find(begin, line.end(), ';');
                    if (end == line.end()) throw ConfigurationException(errorMsg, __FILE__, __FUNCTION__, __LINE__);  // Did not find ';' == very bad
                    
                    std::string substring = line.substr(
                        std::distance(line.begin(), begin),
                        std::distance(begin, end)
                    );

                    parseValueString_(substring);

                    if (end == line.end()) break;
                    iter = ++end;
                    continue;

                }

                iter++;
            }
        }

        inputFileStream.close();
    }

private:
    std::vector<SERVER_TYPE> servers_;

    // Check if string contains only whitespaces
    bool isLineEmpty_(const std::string& line) const{
        if (!line.size()) return true;
        for (size_t i = 0; i < line.size(); i++){
            if (!std::isspace(line[i])) return false;
        }
        return true;
    }

    SERVER_TYPE& getLastServer_(){
        if (!servers_.size()) throw ConfigurationException("Servers are not defined", __FILE__, __FUNCTION__, __LINE__);
        return servers_.back();
    }
    SERVER_TYPE::ROUTE_TYPE& getLastRoute_(){
        return getLastServer_().getRoutes().back();
    }

    HTTP_METHOD stringToHttpMethod(const std::string& str){
        if (str == "GET") return GET;
        else if (str == "POST") return POST;
        else if (str == "DELETE") return DELETE;
        throw ConfigurationException("Invalid HTTP method", __FILE__, __FUNCTION__, __LINE__);
    }
    std::set<std::string> stringToArray(const std::string& str){
        typedef std::string::const_iterator Iterator;
        
        std::set<std::string> result;

        Iterator begin = str.begin();
        Iterator end = str.begin();
        while (end != str.end()) {
            end = std::find(begin, str.end(), ',');
            std::string substring = str.substr(
                std::distance(str.begin(), begin),
                std::distance(begin, end)
            );
            result.insert(substring);
            begin = end + 1;
        }

        return result;
    }
    bool stringToBool(const std::string& str) const {
        if (str == "true") return true;
        else if (str == "false") return false;
        throw ConfigurationException("Invalid boolean value", __FILE__, __FUNCTION__, __LINE__);
    }
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
    std::pair<std::string, std::string> split_(const std::string& str) const {
        typedef std::string::const_iterator Iterator;
        const std::string errorMsg = "Invalid key-value line";

        Iterator splitPoint = std::find(str.begin(), str.end(), ':');
        if (splitPoint == str.end()) throw ConfigurationException(errorMsg, __FILE__, __FUNCTION__, __LINE__);
        if (std::find(splitPoint + 1, str.end(), ':') != str.end()) throw ConfigurationException(errorMsg, __FILE__, __FUNCTION__, __LINE__);

        std::string key = str.substr(0, std::distance(str.begin(), splitPoint));
        std::string value = str.substr(
            std::distance(str.begin(), splitPoint + 1),
            std::distance(splitPoint + 1, str.end())
        );

        return std::make_pair(key, value);
    }
    void parseValueString_(const std::string& str){
        const std::pair<std::string, std::string> key_value = split_(str);
        const std::string& key = key_value.first;
        const std::string& value = key_value.second;

        // Server configs parsing
        SERVER_TYPE& lastServer = getLastServer_();
        if (lastServer.isDone()) throw ConfigurationException("Server finished unexpectedly", __FILE__, __FUNCTION__, __LINE__);
        {
            if (key == "port"){
                lastServer.setPort(stringToNumber<SERVER_TYPE::PORT_TYPE>(value));
                return;
            } else if (key == "host"){
                lastServer.setHost(value);
                return;
            } else if (key == "server_name"){
                lastServer.setServerName(value);
                return;
            } else if (key == "error_pages"){
                std::set<std::string> arr = stringToArray(value);
                for (std::set<std::string>::const_iterator iter = arr.begin(); iter != arr.end(); iter++){
                    lastServer.addErrorPage(*iter);
                }
                return;
            } else if (key == "body_size"){
                lastServer.setBodySize(stringToNumber<SERVER_TYPE::BODY_SIZE_TYPE>(value));
                return;
            }
        }
        
        // Route configs parsing
        SERVER_TYPE::ROUTE_TYPE& lastRoute = getLastRoute_();
        if (lastRoute.isDone()) throw ConfigurationException("Route finished unexpectedly", __FILE__, __FUNCTION__, __LINE__);
        {
            if (key == "methods"){
                std::set<std::string> arr = stringToArray(value);
                for (std::set<std::string>::const_iterator iter = arr.begin(); iter != arr.end(); iter++){
                    lastRoute.addMethod(stringToHttpMethod(*iter));
                }
                return;
            } else if (key == "redir"){
                lastRoute.setRedirection(value);
                return;
            } else if (key == "dir"){
                lastRoute.setDirectory(value);
                return;
            } else if (key == "dir_listening"){
                lastRoute.setDirectoryListening(stringToBool(value));
                return;
            } else if (key == "def_if_dir"){
                lastRoute.setDefaultIfDirectoryResponse(value);
                return;
            } else if (key == "cgi_script"){
                lastRoute.setCgiScriptPath(value);
                return;
            } else if (key == "cgi_bin"){
                lastRoute.setCgiBinPath(value);
                return;
            }
        }

        // Throw an exception on error
        throw ConfigurationException("Invalid key", __FILE__, __FUNCTION__, __LINE__);
    }

};
