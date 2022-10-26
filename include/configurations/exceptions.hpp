#pragma once

#include "utils.hpp"

class Exception {
public:
    Exception(const char* msg) 
        : msg_(std::string(msg)), _file_(""), _function_(""), _line_(0){}
    Exception(const std::string& msg)
        : msg_(msg), _file_(""), _function_(""), _line_(0){}

    Exception(const char* msg, const std::string& _file_, const std::string& _function_, int _line_)
        : msg_(std::string(msg)), _file_(_file_), _function_(_function_), _line_(_line_) {}
    Exception(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_)
        : msg_(msg), _file_(_file_), _function_(_function_), _line_(_line_) {}

    ~Exception() throw(){}

    virtual const std::string what() const throw(){
        return
            "(" +
            _file_ +
            ", " +
            _function_ +
            ", " +
            utilsIntToString(_line_) +
            ") " + 
            output_();
    }

protected:
    const std::string msg_;
    const std::string _file_;
    const std::string _function_;
    const int _line_;

    virtual std::string output_() const {
        return "EXCEPTION: " + msg_;
    }
};

class ConfigurationHostException : public Exception {
public:
    ConfigurationHostException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
        : Exception(msg, _file_, _function_, _line_) {}
    ConfigurationHostException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
        : Exception(msg, _file_, _function_, _line_) {}

    ConfigurationHostException(const char* msg) : Exception(msg){}
    ConfigurationHostException(const std::string& msg) : Exception(msg){}

protected:
    virtual std::string output_() const {
        return "CONFIGURATION_HOST_EXCEPTION: " + msg_;
    }

};

class ConfigurationException : public Exception {
public:
    ConfigurationException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
        : Exception(msg, _file_, _function_, _line_) {}
    ConfigurationException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
        : Exception(msg, _file_, _function_, _line_) {}

    ConfigurationException(const char* msg) : Exception(msg){}
    ConfigurationException(const std::string& msg) : Exception(msg){}

protected:
    virtual std::string output_() const {
        return "CONFIGURATION_EXCEPTION: " + msg_;
    }

};

class ServerException : public Exception {
public:
    ServerException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
        : Exception(msg, _file_, _function_, _line_) {}
    ServerException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
        : Exception(msg, _file_, _function_, _line_) {}

    ServerException(const char* msg) : Exception(msg){}
    ServerException(const std::string& msg) : Exception(msg){}

protected:
    std::string output_() const {
        return "SERVER_EXCEPTION: " + msg_;
    }

};

class RouteException : public Exception {
public:
    RouteException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
        : Exception(msg, _file_, _function_, _line_) {}
    RouteException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
        : Exception(msg, _file_, _function_, _line_) {}

    RouteException(const char* msg) : Exception(msg){}
    RouteException(const std::string& msg) : Exception(msg){}

protected:
    std::string output_() const {
        return "ROUTE_EXCEPTION: " + msg_;
    }

};

