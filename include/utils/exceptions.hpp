#pragma once

#include <string>
#include <typeinfo>

#include "utils.hpp"

#define EXC_ARGS    __FILE__, __FUNCTION__, __LINE__
#define HANDLE_EXC_BEGIN    try {
#define HANDLE_EXC_END      } catch (MAIN_NAMESPACE::UTILS_NAMESPACE::WrapperException& e){ \
                                throw ExceptionType(e.what());                              \
                            }

namespace MAIN_NAMESPACE::UTILS_NAMESPACE{

class Exception {
public:
    Exception(const char* msg);
    Exception(const std::string& msg);

    Exception(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    Exception(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    Exception(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    Exception(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

    ~Exception() throw();

    virtual const std::string what() const throw();
    int getCode();

protected:
    const std::string msg_;
    const std::string _file_;
    const std::string _function_;
    const int _line_;
    const int code_;

    virtual std::string output_() const;
};
    
}
