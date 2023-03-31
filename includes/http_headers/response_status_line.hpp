#pragma once

#include "utils.hpp"
#include "status_line_abstract_parent.hpp"

namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{

class HttpResponseStatusLineException : public MAIN_NAMESPACE::UTILS_NAMESPACE::Exception {
public:
    HttpResponseStatusLineException(const char* msg);
    HttpResponseStatusLineException(const std::string& msg);

    HttpResponseStatusLineException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    HttpResponseStatusLineException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    HttpResponseStatusLineException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    HttpResponseStatusLineException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    virtual std::string output_() const;

};

class HttpResponseStatusLine : public StatusLineAbstractParent{
public:
    typedef HttpResponseStatusLineException ExceptionType;

    HttpResponseStatusLine();
    HttpResponseStatusLine(const HttpResponseStatusLine& other);
    ~HttpResponseStatusLine();

    HttpResponseStatusLine& operator=(const HttpResponseStatusLine& other);

    void setStatusCode(std::string statusCode);
    std::string& getStatusCode();
    const std::string& getStatusCode() const;

    void setMessage(std::string message);
    std::string& getMessage();
    const std::string& getMessage() const;

private:
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> statusCode_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> message_;

    void deleteData_();
    void copyData_(const MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent& o);
    void checkValidity_() const;

};

}
}