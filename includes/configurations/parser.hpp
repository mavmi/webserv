#pragma once

#include "utils.hpp"
#include "configuration.hpp"

namespace MAIN_NAMESPACE{

class ParserException : public MAIN_NAMESPACE::UTILS_NAMESPACE::Exception {
public:
    ParserException(const char* msg);
    ParserException(const std::string& msg);

    ParserException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    ParserException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    ParserException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    ParserException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    virtual std::string output_() const;

};


class Parser{
public:
    typedef ParserException ExceptionType;

    Parser();
    Parser(const std::string& inputFile);
    Parser(const Parser& other);
    
    ~Parser();

    Parser& operator=(const Parser& other);

    const Configuration& parseFile(const std::string& inputFile);
    const Configuration& getConfiguration() const;

private:
    Configuration configuration_;

    // Check if string contains only whitespaces
    bool isLineEmpty_(const std::string& line) const;

    // Return reference to the last server in the list of servers.
    // Throw an exception if there are no servers.
    CONFIG_NAMESPACE::ServerConfiguration& getLastServer_();
    // Return reference to the last route of last server.
    // May throw exception too.
    CONFIG_NAMESPACE::RouteConfiguration& getLastRoute_();

    /*
        All these methods below are about parsing different types
        of strings from an input file.
    */
    MAIN_NAMESPACE::UTILS_NAMESPACE::METHOD stringToHttpMethod_(const std::string& str);
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

};

}
