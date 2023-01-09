#pragma once

#include "utils.hpp"
#include "status_line_abstract_parent.hpp"

namespace MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE{

class HttpRequestStatusLineException : public MAIN_NAMESPACE::UTILS_NAMESPACE::Exception {
public:
    HttpRequestStatusLineException(const char* msg);
    HttpRequestStatusLineException(const std::string& msg);

    HttpRequestStatusLineException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    HttpRequestStatusLineException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    HttpRequestStatusLineException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    HttpRequestStatusLineException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    virtual std::string output_() const;

};


class HttpRequestStatusLine : public StatusLineAbstractParent{
public:
    typedef std::string                                     UrlType;
    typedef MAIN_NAMESPACE::UTILS_NAMESPACE::METHOD         MethodType;
    typedef HttpRequestStatusLineException                  ExceptionType;

    HttpRequestStatusLine();
    HttpRequestStatusLine(const HttpRequestStatusLine& other);
    ~HttpRequestStatusLine();

    HttpRequestStatusLine& operator=(const HttpRequestStatusLine& other);

    void setMethod(MethodType method);
    MethodType& getMethod();
    const MethodType& getMethod() const;

    void setUrl(const UrlType& url);
    UrlType& getUrl();
    const UrlType& getUrl() const;

private:
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<MethodType> method_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<UrlType> url_;

    void deleteData_();
    void copyData_(const MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent& other);
    void checkValidity_() const;

};

}
