#pragma once

#include <stdint.h>

#include "utils.hpp"

namespace MAIN_NAMESPACE{
namespace CONFIG_NAMESPACE{

class ConfigurationPort{
public:
    typedef uint16_t    NumericValueType;
    typedef std::string StringValueType;

    ConfigurationPort();
    ConfigurationPort(NumericValueType port);
    ConfigurationPort(const ConfigurationPort& other);

    ConfigurationPort& operator=(const ConfigurationPort& other);
    
    bool operator==(const ConfigurationPort& other);
    bool operator!=(const ConfigurationPort& other);
    bool operator<(const ConfigurationPort& other);
    bool operator<=(const ConfigurationPort& other);
    bool operator>(const ConfigurationPort& other);
    bool operator>=(const ConfigurationPort& other);

    NumericValueType toNum() const;
    const StringValueType toString() const;
    const char* toCharArray() const;

private:
    NumericValueType port_;

};

bool operator==(const ConfigurationPort& lhs, const ConfigurationPort& rhs);
bool operator!=(const ConfigurationPort& lhs, const ConfigurationPort& rhs);
bool operator<(const ConfigurationPort& lhs, const ConfigurationPort& rhs);
bool operator<=(const ConfigurationPort& lhs, const ConfigurationPort& rhs);
bool operator>(const ConfigurationPort& lhs, const ConfigurationPort& rhs);
bool operator>=(const ConfigurationPort& lhs, const ConfigurationPort& rhs);

}
}