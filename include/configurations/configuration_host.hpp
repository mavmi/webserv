#pragma once

#include "utils.hpp"
#include "exceptions.hpp"

namespace configuration {

// This class contains IP address.
// Some of it's methods may throw ConfigurationHostException on error.
class ConfigurationHost{
public:
    typedef uint8_t         ValueType;
    typedef size_t          SizeType;

    ConfigurationHost(ValueType b1, ValueType b2, ValueType b3, ValueType b4);
    ConfigurationHost(const ConfigurationHost& other);
    ConfigurationHost(const std::string& hostStr);

    ConfigurationHost& operator=(const ConfigurationHost& other);
    ConfigurationHost& operator=(const std::string& hostStr);

    bool operator==(const ConfigurationHost& other) const;
    bool operator!=(const ConfigurationHost& other) const;

    // Return string representation of IP address.
    std::string toString() const;
    // Get number from IP at specified position.
    // May throw an exception on if position is invalid.
    ValueType at(SizeType position) const;

    // Set IP number to specified position.
    // May throw an exception on if position is invalid.
    void set(ValueType value, SizeType position);

private:
    const static SizeType maxSize_ = 4;
    ValueType ip_[maxSize_];

    // Convert VALUE_TYPE to string.
    std::string toString_(ValueType val) const;

    // Convert string number to VALUE_TYPE.
    // May throw exception.
    ValueType stringToNumber_(const std::string& str) const;

};

}
