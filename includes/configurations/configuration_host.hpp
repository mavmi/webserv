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
    typedef uint8_t         ValueType;
    typedef size_t          SizeType;

    ConfigurationHost();
    ConfigurationHost(ValueType b1, ValueType b2, ValueType b3, ValueType b4);
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
    ValueType at(SizeType position) const;

    // Set IP number to specified position.
    // May throw an exception on if position is invalid.
    void set(ValueType value, SizeType position);

private:
    const static SizeType maxSize_ = 4;
    ValueType ip_[maxSize_];

    // Convert string number to VALUE_TYPE.
    // May throw exception.
    ValueType stringToNumber_(const std::string& str) const;

};

}
}