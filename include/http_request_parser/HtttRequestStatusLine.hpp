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
friend HttpRequestParser;
public:
    typedef std::string                     URL_TYPE;
    typedef double                          HTTP_VERSION_TYPE;
    typedef HttpRequestStatusLineException  ExceptionType;

    enum METHOD{
        GET,
        POST,
        DELETE
    };

    ~HttpRequestStatusLine();

    void setMethod(METHOD method);
    METHOD& getMethod();
    const METHOD& getMethod() const;

    void setUrl(const URL_TYPE& url);
    URL_TYPE& getUrl();
    const URL_TYPE& getUrl() const;

    void setHttpVersion(HTTP_VERSION_TYPE httpVersion);
    HTTP_VERSION_TYPE& getHttpVersion();
    const HTTP_VERSION_TYPE& getHttpVersion() const;

private:
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<METHOD> method_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<URL_TYPE> url_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<HTTP_VERSION_TYPE> httpVersion_;

    HttpRequestStatusLine();
    HttpRequestStatusLine(const HttpRequestStatusLine& other);

    HttpRequestStatusLine& operator=(const HttpRequestStatusLine& other);

    void deleteData_();
    void copyData_(const MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent& other);
    void checkValidity_() const;
    void throwOnDone_() const;

};

}
