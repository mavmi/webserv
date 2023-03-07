#pragma once

#include "utils.hpp"
#include "../http_headers/request_status_line.hpp"
#include "../http_headers/general_headers.hpp"
#include "../http_headers/request_headers.hpp"

namespace MAIN_NAMESPACE{
namespace HTTP_REQUEST_PARS_NAMESPACE{

class HttpRequestException : public MAIN_NAMESPACE::UTILS_NAMESPACE::Exception {
public:
    HttpRequestException(const char* msg);
    HttpRequestException(const std::string& msg);

    HttpRequestException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    HttpRequestException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    HttpRequestException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    HttpRequestException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    virtual std::string output_() const;

};

class HttpRequest{
public:
    typedef HttpRequestException  ExceptionType;

    HttpRequest();
    HttpRequest(const MAIN_NAMESPACE::UTILS_NAMESPACE::BytesContainer& buffer);
    HttpRequest(const HttpRequest& other);

    ~HttpRequest();

    HttpRequest& operator=(const HttpRequest& other);

    MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpRequestStatusLine& getStatusLine();
    const MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpRequestStatusLine& getStatusLine() const;

    MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeaders& getGeneralHeaders();
    const MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeaders& getGeneralHeaders() const;

    MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpRequestHeaders& getRequestHeaders();
    const MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpRequestHeaders& getRequestHeaders() const;
    
    std::vector<std::string>& getRequestContent();
    const std::vector<std::string>& getRequestContent() const;

private:
    MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpRequestStatusLine httpRequestStatusLine_;
    MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeaders httpGeneralHeaders_;
    MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpRequestHeaders httpRequestHeaders_;
    std::vector<std::string> httpRequestContent_;

};

}
}
