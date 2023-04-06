#pragma once

#include "request_status_line.hpp"

#include "../utils/utils.hpp"

namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{

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
    typedef HttpHeadersAbstractParentException              ExceptionType;

protected:
    const StatusLineAbstractParent& statusLine_;

    HttpHeadersAbstractParent(const StatusLineAbstractParent& statusLine);
    HttpHeadersAbstractParent(const HttpHeadersAbstractParent& other);
    ~HttpHeadersAbstractParent();

    HttpHeadersAbstractParent& operator=(const HttpHeadersAbstractParent&);

    virtual MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_VERSION getHttpVersion_() const;
    virtual void checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_VERSION version);

    std::string generateDate_(std::tm* time) const;

};

}
}
