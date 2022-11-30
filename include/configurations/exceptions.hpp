#pragma once

#include "utils.hpp"

#define EXC_ARGS    __FILE__, __FUNCTION__, __LINE__

/*
    A bunch of exceptions for configuration classes.
*/

namespace wsrv::configuration {

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

class ConfigurationHostException : public Exception {
public:
    ConfigurationHostException(const char* msg);
    ConfigurationHostException(const std::string& msg);

    ConfigurationHostException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    ConfigurationHostException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    ConfigurationHostException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    ConfigurationHostException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    virtual std::string output_() const;

};

class ConfigurationException : public Exception {
public:
    ConfigurationException(const char* msg);
    ConfigurationException(const std::string& msg);

    ConfigurationException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    ConfigurationException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    ConfigurationException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    ConfigurationException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    virtual std::string output_() const;

};

class ServerException : public Exception {
public:
    ServerException(const char* msg);
    ServerException(const std::string& msg);

    ServerException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    ServerException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    ServerException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    ServerException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    std::string output_() const;

};

class RouteException : public Exception {
public:
    RouteException(const char* msg);
    RouteException(const std::string& msg);

    RouteException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    RouteException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    RouteException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    RouteException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    std::string output_() const;

};

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

class ContainerException : public Exception {
public:
    ContainerException(const char* msg);
    ContainerException(const std::string& msg);

    ContainerException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    ContainerException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    ContainerException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    ContainerException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    std::string output_() const;

};

}
