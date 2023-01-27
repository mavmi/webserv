#include "../../include/utils/wrapper.hpp"

namespace MAIN_NAMESPACE{
namespace UTILS_NAMESPACE{

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

}
}