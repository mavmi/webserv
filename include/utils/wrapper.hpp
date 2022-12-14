#pragma once

#include "utils.hpp"
#include "exceptions.hpp"

namespace MAIN_NAMESPACE::UTILS_NAMESPACE{

class WrapperException : public Exception {
public:
    WrapperException(const char* msg);
    WrapperException(const std::string& msg);

    WrapperException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    WrapperException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    WrapperException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    WrapperException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    std::string output_() const;

};

template <typename T>
class Wrapper{
public:
    typedef WrapperException    ExceptionType;

    Wrapper(){
        isSet_ = false;
    }
    Wrapper(const Wrapper& other)
        : value_(other.value_), isSet_(other.isSet_) {

    }
    Wrapper(const T& value)
        : value_(value), isSet_(true) {

    }
    ~Wrapper(){}

    Wrapper& operator=(const Wrapper& other){
        value_ = other.value_;
        isSet_ = other.isSet_;
        return *this;
    }

    T& get(){
        if (!isSet_) throw ExceptionType(std::string("Trying to get reference to non-set value of type ") + std::string(typeid(T).name()), EXC_ARGS);
        return value_;
    }
    const T& get() const{
        if (!isSet_) throw ExceptionType(std::string("Trying to get reference to non-set value") + std::string(typeid(T).name()), EXC_ARGS);
        return value_;
    }

    void set(const T& value){
        value_ = value;
        isSet_ = true;
    }

    bool isSet() const {
        return isSet_;
    }

private:
    T value_;
    bool isSet_;

};

}
