#pragma once

#include "utils.hpp"

namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{

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


class HttpRequestStatusLine : public MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent{
public:
    typedef std::string                                     UrlType;
    typedef MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_VERSION   HttpVersionType;
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

    void setHttpVersion(HttpVersionType httpVersion);
    HttpVersionType& getHttpVersion();
    const HttpVersionType& getHttpVersion() const;

private:
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<MethodType> method_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<UrlType> url_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<HttpVersionType> httpVersion_;

    void deleteData_();
    void copyData_(const MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent& other);
    void checkValidity_() const;
    void throwOnDone_() const;

};

}
