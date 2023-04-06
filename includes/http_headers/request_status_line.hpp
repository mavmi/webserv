#pragma once

#include "utils.hpp"
#include "status_line_abstract_parent.hpp"

namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{

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
    typedef HttpRequestStatusLineException                  ExceptionType;

    HttpRequestStatusLine();
    HttpRequestStatusLine(const HttpRequestStatusLine& other);
    ~HttpRequestStatusLine();

    HttpRequestStatusLine& operator=(const HttpRequestStatusLine& other);

    void setMethod(MAIN_NAMESPACE::UTILS_NAMESPACE::METHOD method);
    MAIN_NAMESPACE::UTILS_NAMESPACE::METHOD& getMethod();
    const MAIN_NAMESPACE::UTILS_NAMESPACE::METHOD& getMethod() const;

    void setUrl(const std::string& url);
    std::string& getUrl();
    const std::string& getUrl() const;

private:
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<MAIN_NAMESPACE::UTILS_NAMESPACE::METHOD> method_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> url_;

    void deleteData_();
    void copyData_(const MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent& other);
    void checkValidity_() const;

};

}
}
