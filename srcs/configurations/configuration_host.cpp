#include "../../include/configurations/configuration_host.hpp"

ConfigurationHost::ConfigurationHost(VALUE_TYPE b1, VALUE_TYPE b2, VALUE_TYPE b3, VALUE_TYPE b4){
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
    for (SIZE_TYPE i = 0; i < maxSize_; i++) ip_[i] = other.ip_[i];
    return *this;
}
ConfigurationHost& ConfigurationHost::operator=(const std::string& hostStr){
    const std::string errorStr = "Invalid host string";
    SIZE_TYPE counter = 0;
    VALUE_TYPE numbers[maxSize_];

    std::string::const_iterator begin = hostStr.begin();
    while (counter < maxSize_){
        std::string::const_iterator end = std::find(begin, hostStr.end(), '.');
        std::string substr = hostStr.substr(
            std::distance(hostStr.begin(), begin),  // position of substring beginning
            std::distance(begin, end)               // substring length
        );

        numbers[counter++] = toNum_(substr);
        if ((counter == maxSize_ && end != hostStr.end()) || 
                (counter != maxSize_ && end == hostStr.end())){
            throw ConfigurationHostException(errorStr, __FILE__, __FUNCTION__, __LINE__);
        }

        begin = ++end;
    }

    if (counter != maxSize_) throw ConfigurationHostException(errorStr, __FILE__, __FUNCTION__, __LINE__);
    for (SIZE_TYPE i = 0; i < maxSize_; i++) ip_[i] = numbers[i];
    return *this;
}

std::string ConfigurationHost::toString() const {
    std::string str = "";

    for (SIZE_TYPE i = 0; i < maxSize_; i++){
        str += toString_(ip_[i]);
        if (i + 1 != maxSize_){
            str += '.';
        }
    }

    return str;
}
ConfigurationHost::VALUE_TYPE ConfigurationHost::at(SIZE_TYPE position) const {
    if (position > maxSize_) throw ConfigurationHostException("Bad IP position", __FILE__, __FUNCTION__, __LINE__);
    return ip_[position];
}

void ConfigurationHost::set(VALUE_TYPE value, SIZE_TYPE position){
    if (position > maxSize_) throw ConfigurationHostException("Bad IP position", __FILE__, __FUNCTION__, __LINE__);
    ip_[position] = value;  
}

std::string ConfigurationHost::toString_(VALUE_TYPE val) const {
    if (val == 0) return "0";
    
    std::string result = "";

    while (val > 0){
        result += '0' + val % 10;
        val /= 10;
    }

    std::reverse(result.begin(), result.end());
    return result;
}

ConfigurationHost::VALUE_TYPE ConfigurationHost::toNum_(const std::string& str) const {
    if (!str.size()) throw ConfigurationHostException("Empty num string", __FILE__, __FUNCTION__, __LINE__);

    int res = 0;
    for (SIZE_TYPE i = 0; i < str.size(); i++){
        char c = str.at(i);
        if (c < '0' || c > '9') throw ConfigurationHostException("Invalid num string", __FILE__, __FUNCTION__, __LINE__);
        res = res * 10 + (str.at(i) - '0');
    }

    if (res < 0 || res > 255) throw ConfigurationHostException("Num string value too big", __FILE__, __FUNCTION__, __LINE__);
    return static_cast<VALUE_TYPE>(res);
}
