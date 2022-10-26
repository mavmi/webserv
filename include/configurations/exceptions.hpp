#pragma once

#include "utils.hpp"

class Exception {
public:
    Exception(const char* msg);
    Exception(const std::string& msg);

    Exception(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    Exception(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);
    ~Exception() throw();

    virtual const std::string what() const throw();

protected:
    const std::string msg_;
    const std::string _file_;
    const std::string _function_;
    const int _line_;

    virtual std::string output_() const;
};

class ConfigurationHostException : public Exception {
public:
    ConfigurationHostException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    ConfigurationHostException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    ConfigurationHostException(const char* msg);
    ConfigurationHostException(const std::string& msg);

protected:
    virtual std::string output_() const;

};

class ConfigurationException : public Exception {
public:
    ConfigurationException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    ConfigurationException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    ConfigurationException(const char* msg);
    ConfigurationException(const std::string& msg);

protected:
    virtual std::string output_() const;

};

class ServerException : public Exception {
public:
    ServerException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    ServerException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    ServerException(const char* msg);
    ServerException(const std::string& msg);

protected:
    std::string output_() const;

};

class RouteException : public Exception {
public:
    RouteException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    RouteException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    RouteException(const char* msg);
    RouteException(const std::string& msg);

protected:
    std::string output_() const;

};

