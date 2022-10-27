#pragma once

#include "utils.hpp"
#include "exceptions.hpp"

// This class contains IP address.
// Some of it's methods may throw ConfigurationHostException on error.
class ConfigurationHost{
public:
    typedef unsigned char   VALUE_TYPE;
    typedef size_t          SIZE_TYPE;

    ConfigurationHost(VALUE_TYPE b1, VALUE_TYPE b2, VALUE_TYPE b3, VALUE_TYPE b4);
    ConfigurationHost(const ConfigurationHost& other);
    ConfigurationHost(const std::string& hostStr);

    ConfigurationHost& operator=(const ConfigurationHost& other);
    ConfigurationHost& operator=(const std::string& hostStr);

    // Return string representation of IP address.
    std::string toString() const;
    // Get number from IP at specified position.
    // May throw an exception on if position is invalid.
    VALUE_TYPE at(SIZE_TYPE position) const;

    // Set IP number to specified position.
    // May throw an exception on if position is invalid.
    void set(VALUE_TYPE value, SIZE_TYPE position);

private:
    const static SIZE_TYPE maxSize_ = 4;
    VALUE_TYPE ip_[maxSize_];

    // Convert VALUE_TYPE to string.
    std::string toString_(VALUE_TYPE val) const;

    // Convert string number to VALUE_TYPE.
    // May throw exception.
    VALUE_TYPE stringToNumber_(const std::string& str) const;

};
