#include "../../includes/utils/container.hpp"

namespace MAIN_NAMESPACE{
namespace UTILS_NAMESPACE{

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
}