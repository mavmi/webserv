#include "../../includes/utils/utils.hpp"

namespace MAIN_NAMESPACE{
namespace UTILS_NAMESPACE{

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

}
}