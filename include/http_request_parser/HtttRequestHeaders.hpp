#pragma once

#include "utils.hpp"

namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{

class HttpRequestHeadersException : public MAIN_NAMESPACE::UTILS_NAMESPACE::Exception {
public:
    HttpRequestHeadersException(const char* msg);
    HttpRequestHeadersException(const std::string& msg);

    HttpRequestHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    HttpRequestHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    HttpRequestHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    HttpRequestHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    virtual std::string output_() const;

};


class HttpRequestHeaders{
friend HttpRequestParser;
public:
    ~HttpRequestHeaders();

private:
    /*
        Bunch of wrappers must be here
    */

    HttpRequestHeaders();
    HttpRequestHeaders(const HttpRequestHeaders& other);

    HttpRequestHeaders& operator=(const HttpRequestHeaders& other);

};

}
