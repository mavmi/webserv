#pragma once

#include <vector>
#include <sstream>
#include <stddef.h>

#include "utils.hpp"
#include "../http_headers/request_status_line.hpp"
#include "../http_headers/general_headers.hpp"
#include "../http_headers/request_headers.hpp"

namespace MAIN_NAMESPACE{
namespace HTTP_REQUEST_PARS_NAMESPACE{

class HttpRequestParserException : public MAIN_NAMESPACE::UTILS_NAMESPACE::Exception {
public:
    HttpRequestParserException(const char* msg);
    HttpRequestParserException(const std::string& msg);

    HttpRequestParserException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    HttpRequestParserException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    HttpRequestParserException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    HttpRequestParserException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    virtual std::string output_() const;

};


class HttpRequestParser{
public:
    typedef size_t                      SizeType;
    typedef char*                       BufferType;
    typedef std::vector<BufferType>     BufferContainerType;
    typedef HttpRequestParserException  ExceptionType;

    HttpRequestParser();
    HttpRequestParser(const HttpRequestParser& other);
    ~HttpRequestParser();

    HttpRequestParser& operator=(const HttpRequestParser& other);

    void parseHttpRequest(const MAIN_NAMESPACE::UTILS_NAMESPACE::BytesContainer& buffer);
    void clear();

    const MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpRequestStatusLine& getStatusLine() const;
    const MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeaders& getGeneralHeaders() const;
    const MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpRequestHeaders& getRequestHeaders() const;
    const std::vector<std::string>& getRequestContent() const;

private:
    MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpRequestStatusLine httpRequestStatusLine_;
    MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeaders httpGeneralHeaders_;
    MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpRequestHeaders httpRequestHeaders_;
    std::vector<std::string> httpRequestContent_;

    std::vector<std::string> split_(const std::string& str, char delimiter);
    int find_(char* arr, int startPoint, int size, char c);
    bool isLineEmpty_(const std::string& line);

    std::vector<std::string> parseBuffer_(const MAIN_NAMESPACE::UTILS_NAMESPACE::BytesContainer& buffer);
    void parseStatusLine_(const std::string& line);
    void parseHeader_(const std::string& line);
};

}
}
