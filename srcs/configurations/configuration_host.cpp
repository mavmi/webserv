#include "../../include/configurations/configuration_host.hpp"

namespace configuration {

ConfigurationHost::ConfigurationHost(){
    ip_[0] = 0;
    ip_[1] = 0;
    ip_[2] = 0;
    ip_[3] = 0;
}
ConfigurationHost::ConfigurationHost(ValueType b1, ValueType b2, ValueType b3, ValueType b4){
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
    for (SizeType i = 0; i < maxSize_; i++) ip_[i] = other.ip_[i];
    return *this;
}
ConfigurationHost& ConfigurationHost::operator=(const std::string& hostStr){
    const std::string errorStr = "Invalid host string";
    SizeType counter = 0;
    ValueType numbers[maxSize_];

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
    for (SizeType i = 0; i < maxSize_; i++) ip_[i] = numbers[i];
    return *this;
}

bool ConfigurationHost::operator==(const ConfigurationHost& other) const{
    for (SizeType i = 0; i < maxSize_; i++){
        if (ip_[i] != other.ip_[i]) return false;
    }
    return true;
}
bool ConfigurationHost::operator!=(const ConfigurationHost& other) const{
    return !(*this == other);
}
bool ConfigurationHost::operator<(const ConfigurationHost& other) const{
    for (SizeType i = 0; i < maxSize_; i++){
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

    for (SizeType i = 0; i < maxSize_; i++){
        str += toString_(ip_[i]);
        if (i + 1 != maxSize_){
            str += '.';
        }
    }

    return str;
}
ConfigurationHost::ValueType ConfigurationHost::at(SizeType position) const {
    if (position > maxSize_) throw ConfigurationHostException("Bad IP position", EXC_ARGS);
    return ip_[position];
}

void ConfigurationHost::set(ValueType value, SizeType position){
    if (position > maxSize_) throw ConfigurationHostException("Bad IP position", EXC_ARGS);
    ip_[position] = value;  
}

std::string ConfigurationHost::toString_(ValueType val) const {
    return utilsNumToString<ValueType>(val);
}

ConfigurationHost::ValueType ConfigurationHost::stringToNumber_(const std::string& str) const {
    try {
        if (str.size() > 3) throw UtilsException("Numeric value too long");
        return utilsStringToNum<ValueType>(str);
    } catch (UtilsException& e) {
        throw ConfigurationHostException(e.what(), EXC_ARGS);
    }
}

} 
