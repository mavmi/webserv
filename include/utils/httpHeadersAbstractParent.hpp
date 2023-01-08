#pragma once

#include "utils.hpp"
#include "../http_request_parser/HtttRequestStatusLine.hpp"

namespace MAIN_NAMESPACE::UTILS_NAMESPACE{

class HttpHeadersAbstractParentException : public MAIN_NAMESPACE::UTILS_NAMESPACE::Exception {
public:
    HttpHeadersAbstractParentException(const char* msg);
    HttpHeadersAbstractParentException(const std::string& msg);

    HttpHeadersAbstractParentException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    HttpHeadersAbstractParentException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    HttpHeadersAbstractParentException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    HttpHeadersAbstractParentException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    virtual std::string output_() const;

};


class HttpHeadersAbstractParent{
public:
    typedef MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE::HttpRequestStatusLine::HTTP_VERSION_TYPE   HttpVersionType;
    typedef HttpHeadersAbstractParentException                                                      ExceptionType;

protected:
    const MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE::HttpRequestStatusLine& statusLine_;

    HttpHeadersAbstractParent(const MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE::HttpRequestStatusLine& statusLine);
    HttpHeadersAbstractParent(const HttpHeadersAbstractParent& other);
    ~HttpHeadersAbstractParent();

    HttpHeadersAbstractParent& operator=(const HttpHeadersAbstractParent&);

    virtual HttpVersionType getHttpVersion_() const;
    virtual void checkVersion_(HttpVersionType version);

};

}
