#include "../../includes/configurations/configuration_host.hpp"

namespace MAIN_NAMESPACE{
namespace CONFIG_NAMESPACE{
ConfigurationHostException::ConfigurationHostException(const char* msg) : Exception(msg){}
ConfigurationHostException::ConfigurationHostException(const std::string& msg) : Exception(msg){}
ConfigurationHostException::ConfigurationHostException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
ConfigurationHostException::ConfigurationHostException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
ConfigurationHostException::ConfigurationHostException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
ConfigurationHostException::ConfigurationHostException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string ConfigurationHostException::output_() const {
    return "CONFIGURATION_HOST_EXCEPTION: " + msg_;
}
}
}


namespace MAIN_NAMESPACE{
namespace CONFIG_NAMESPACE{
ConfigurationHost::ConfigurationHost(){
    ip_[0] = 0;
    ip_[1] = 0;
    ip_[2] = 0;
    ip_[3] = 0;
}
ConfigurationHost::ConfigurationHost(uint8_t b1, uint8_t b2, uint8_t b3, uint8_t b4){
    ip_[0] = b1;
    ip_[1] = b2;
    ip_[2] = b3;
    ip_[3] = b4;
}
ConfigurationHost::ConfigurationHost(const ConfigurationHost& other){
    operator=(other);
}
ConfigurationHost::ConfigurationHost(const std::string& hostStr){
    operator=(hostStr);
}

ConfigurationHost& ConfigurationHost::operator=(const ConfigurationHost& other){
    for (size_t i = 0; i < maxSize_; i++) ip_[i] = other.ip_[i];
    return *this;
}
ConfigurationHost& ConfigurationHost::operator=(const std::string& hostStr){
    const std::string errorStr = "Invalid host string";
    size_t counter = 0;
    uint8_t numbers[maxSize_];

    std::string::const_iterator begin = hostStr.begin();
    while (counter < maxSize_){
        std::string::const_iterator end = std::find(begin, hostStr.end(), '.');
        std::string substr = hostStr.substr(
            std::distance(hostStr.begin(), begin),  // position of substring beginning
            std::distance(begin, end)               // substring length
        );

        numbers[counter++] = stringToNumber_(substr);
        if ((counter == maxSize_ && end != hostStr.end()) || 
                (counter != maxSize_ && end == hostStr.end())){
            throw ConfigurationHostException(errorStr, EXC_ARGS);
        }

        begin = ++end;
    }

    if (counter != maxSize_) throw ConfigurationHostException(errorStr, EXC_ARGS);
    for (size_t i = 0; i < maxSize_; i++) ip_[i] = numbers[i];
    return *this;
}

bool ConfigurationHost::operator==(const ConfigurationHost& other) const{
    for (size_t i = 0; i < maxSize_; i++){
        if (ip_[i] != other.ip_[i]) return false;
    }
    return true;
}
bool ConfigurationHost::operator!=(const ConfigurationHost& other) const{
    return !(*this == other);
}
bool ConfigurationHost::operator<(const ConfigurationHost& other) const{
    for (size_t i = 0; i < maxSize_; i++){
        if (ip_[i] < other.ip_[i]) return true;
        else if (ip_[i] > other.ip_[i]) return false;
    }
    return false;
}
bool ConfigurationHost::operator<=(const ConfigurationHost& other) const{
    return (*this < other || *this == other);
}
bool ConfigurationHost::operator>(const ConfigurationHost& other) const{
    return !(*this <= other);
}
bool ConfigurationHost::operator>=(const ConfigurationHost& other) const{
    return (*this > other || *this == other);
}

std::string ConfigurationHost::toString() const {
    std::string str = "";

    for (size_t i = 0; i < maxSize_; i++){
        str += MAIN_NAMESPACE::UTILS_NAMESPACE::utilsNumToString<uint8_t>(ip_[i]);
        if (i + 1 != maxSize_){
            str += '.';
        }
    }

    return str;
}
MAIN_NAMESPACE::UTILS_NAMESPACE::ArrayContainer ConfigurationHost::toCharArray() const{
    return MAIN_NAMESPACE::UTILS_NAMESPACE::ArrayContainer::fromString(toString());
}
uint8_t ConfigurationHost::at(size_t position) const {
    if (position > maxSize_) throw ConfigurationHostException("Bad IP position", EXC_ARGS);
    return ip_[position];
}

void ConfigurationHost::set(uint8_t value, size_t position){
    if (position > maxSize_) throw ConfigurationHostException("Bad IP position", EXC_ARGS);
    ip_[position] = value;  
}

uint8_t ConfigurationHost::stringToNumber_(const std::string& str) const {
    try {
        if (str.size() > 3) throw MAIN_NAMESPACE::UTILS_NAMESPACE::UtilsException("Numeric value too long");
        return MAIN_NAMESPACE::UTILS_NAMESPACE::utilsStringToNum<uint8_t>(str);
    } catch (MAIN_NAMESPACE::UTILS_NAMESPACE::UtilsException& e) {
        throw ConfigurationHostException(e.what(), EXC_ARGS);
    }
}
} 
}