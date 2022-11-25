#include "../../include/configurations/exceptions.hpp"

namespace configuration {

Exception::Exception(const char* msg) 
    : msg_(std::string(msg)), _file_(""), _function_(""), _line_(0), code_(0){}
Exception::Exception(const std::string& msg)
    : msg_(msg), _file_(""), _function_(""), _line_(0), code_(0){}
Exception::Exception(const char* msg, const std::string& _file_, const std::string& _function_, int _line_)
    : msg_(std::string(msg)), _file_(_file_), _function_(_function_), _line_(_line_), code_(0) {}
Exception::Exception(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_)
    : msg_(msg), _file_(_file_), _function_(_function_), _line_(_line_), code_(0) {}
Exception::Exception(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : msg_(std::string(msg)), _file_(_file_), _function_(_function_), _line_(_line_), code_(code) {}
Exception::Exception(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : msg_(msg), _file_(_file_), _function_(_function_), _line_(_line_), code_(code) {}
Exception::~Exception() throw(){}
const std::string Exception::what() const throw(){
    return
        "(" +
        _file_ +
        ", " +
        _function_ +
        ", " +
        utilsNumToString<int>(_line_) +
        ") " + 
        output_();
}
int Exception::getCode(){
    return code_;
}
std::string Exception::output_() const {
    return "EXCEPTION: " + msg_;
}


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


ConfigurationException::ConfigurationException(const char* msg) : Exception(msg){}
ConfigurationException::ConfigurationException(const std::string& msg) : Exception(msg){}
ConfigurationException::ConfigurationException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
ConfigurationException::ConfigurationException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
ConfigurationException::ConfigurationException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
ConfigurationException::ConfigurationException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string ConfigurationException::output_() const {
    return "CONFIGURATION_EXCEPTION: " + msg_;
}


ServerException::ServerException(const char* msg) : Exception(msg){}
ServerException::ServerException(const std::string& msg) : Exception(msg){}
ServerException::ServerException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
ServerException::ServerException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
ServerException::ServerException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
ServerException::ServerException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string ServerException::output_() const {
    return "SERVER_EXCEPTION: " + msg_;
}


RouteException::RouteException(const char* msg) : Exception(msg){}
RouteException::RouteException(const std::string& msg) : Exception(msg){}
RouteException::RouteException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
RouteException::RouteException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
RouteException::RouteException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
RouteException::RouteException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string RouteException::output_() const {
    return "ROUTE_EXCEPTION: " + msg_;
}


WrapperException::WrapperException(const char* msg) : Exception(msg){}
WrapperException::WrapperException(const std::string& msg) : Exception(msg){}
WrapperException::WrapperException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
WrapperException::WrapperException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
WrapperException::WrapperException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
WrapperException::WrapperException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string WrapperException::output_() const {
    return "WRAPPER_EXCEPTION: " + msg_;
}


ContainerException::ContainerException(const char* msg) : Exception(msg){}
ContainerException::ContainerException(const std::string& msg) : Exception(msg){}
ContainerException::ContainerException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
ContainerException::ContainerException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
ContainerException::ContainerException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
ContainerException::ContainerException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string ContainerException::output_() const {
    return "CONTAINER_EXCEPTION: " + msg_;
}

}
