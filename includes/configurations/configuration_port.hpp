#pragma once

#include <stdint.h>

#include "utils.hpp"

namespace MAIN_NAMESPACE{
namespace CONFIG_NAMESPACE{

class ConfigurationPort{
public:
    ConfigurationPort();
    ConfigurationPort(uint16_t port);
    ConfigurationPort(const ConfigurationPort& other);

    ConfigurationPort& operator=(const ConfigurationPort& other);
    
    bool operator==(const ConfigurationPort& other) const;
    bool operator!=(const ConfigurationPort& other) const;
    bool operator<(const ConfigurationPort& other) const;
    bool operator<=(const ConfigurationPort& other) const;
    bool operator>(const ConfigurationPort& other) const;
    bool operator>=(const ConfigurationPort& other) const;

    uint16_t toNum() const;
    std::string toString() const;
    MAIN_NAMESPACE::UTILS_NAMESPACE::ArrayContainer toCharArray() const;

private:
    uint16_t port_;

};

}
}