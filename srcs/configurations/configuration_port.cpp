#include "../../includes/configurations/configuration_port.hpp"

namespace MAIN_NAMESPACE{
namespace CONFIG_NAMESPACE{

ConfigurationPort::ConfigurationPort(){
    port_ = 0;
}
ConfigurationPort::ConfigurationPort(NumericValueType port){
    port_ = port;
}
ConfigurationPort::ConfigurationPort(const ConfigurationPort& other){
    port_ = other.port_;
}

ConfigurationPort& ConfigurationPort::operator=(const ConfigurationPort& other){
    port_ = other.port_;
    return *this;
}

bool ConfigurationPort::operator==(const ConfigurationPort& other) const {
    return port_ == other.port_;
}
bool ConfigurationPort::operator!=(const ConfigurationPort& other) const {
    return port_ != other.port_;
}
bool ConfigurationPort::operator<(const ConfigurationPort& other) const {
    return port_ < other.port_;
}
bool ConfigurationPort::operator<=(const ConfigurationPort& other) const {
    return port_ <= other.port_;
}
bool ConfigurationPort::operator>(const ConfigurationPort& other) const {
    return port_ > other.port_;
}
bool ConfigurationPort::operator>=(const ConfigurationPort& other) const {
    return port_ >= other.port_;
}

ConfigurationPort::NumericValueType ConfigurationPort::toNum() const{
    return port_;
}
std::string ConfigurationPort::toString() const{
    return MAIN_NAMESPACE::UTILS_NAMESPACE::utilsNumToString<NumericValueType>(port_);
}
MAIN_NAMESPACE::UTILS_NAMESPACE::ArrayContainer ConfigurationPort::toCharArray() const{
    return MAIN_NAMESPACE::UTILS_NAMESPACE::ArrayContainer::fromString(toString());

}

}
}
