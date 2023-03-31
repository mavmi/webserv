#pragma once

#include "utils.hpp"

namespace MAIN_NAMESPACE{
namespace CONFIG_NAMESPACE{

class ConfigurationHostException : public MAIN_NAMESPACE::UTILS_NAMESPACE::Exception {
public:
    ConfigurationHostException(const char* msg);
    ConfigurationHostException(const std::string& msg);

    ConfigurationHostException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    ConfigurationHostException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    ConfigurationHostException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    ConfigurationHostException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    virtual std::string output_() const;

};


// This class contains IP address.
// Some of it's methods may throw ConfigurationHostException on error.
class ConfigurationHost{
public:
    ConfigurationHost();
    ConfigurationHost(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4);
    ConfigurationHost(const ConfigurationHost& other);
    ConfigurationHost(const std::string& hostStr);
    ~ConfigurationHost(){}

    ConfigurationHost& operator=(const ConfigurationHost& other);
    ConfigurationHost& operator=(const std::string& hostStr);

    bool operator==(const ConfigurationHost& other) const;
    bool operator!=(const ConfigurationHost& other) const;
    bool operator<(const ConfigurationHost& other) const;
    bool operator<=(const ConfigurationHost& other) const;
    bool operator>(const ConfigurationHost& other) const;
    bool operator>=(const ConfigurationHost& other) const;

    // Return string representation of IP address.
    std::string toString() const;
    MAIN_NAMESPACE::UTILS_NAMESPACE::ArrayContainer toCharArray() const;
    // Get number from IP at specified position.
    // May throw an exception on if position is invalid.
    uint8_t at(size_t position) const;

    // Set IP number to specified position.
    // May throw an exception on if position is invalid.
    void set(uint8_t value, size_t position);

private:
    const static size_t maxSize_ = 4;
    uint8_t ip_[maxSize_];

    // Convert string number to VALUE_TYPE.
    // May throw exception.
    uint8_t stringToNumber_(const std::string& str) const;

};

}
}
