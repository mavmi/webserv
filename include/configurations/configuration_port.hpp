#pragma once

#include <stdint.h>

#include "utils.hpp"

namespace MAIN_NAMESPACE{
namespace CONFIG_NAMESPACE{

class ConfigurationPort{
public:
    typedef uint16_t    NumericValueType;

    ConfigurationPort();
    ConfigurationPort(NumericValueType port);
    ConfigurationPort(const ConfigurationPort& other);

    ConfigurationPort& operator=(const ConfigurationPort& other);
    
    bool operator==(const ConfigurationPort& other) const;
    bool operator!=(const ConfigurationPort& other) const;
    bool operator<(const ConfigurationPort& other) const;
    bool operator<=(const ConfigurationPort& other) const;
    bool operator>(const ConfigurationPort& other) const;
    bool operator>=(const ConfigurationPort& other) const;

    NumericValueType toNum() const;
    std::string toString() const;
    MAIN_NAMESPACE::UTILS_NAMESPACE::ArrayContainer toCharArray() const;

private:
    NumericValueType port_;

};

}
}