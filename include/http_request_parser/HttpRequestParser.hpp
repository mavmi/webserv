#pragma once

#include <vector>
#include <sstream>
#include <stddef.h>

#include "utils.hpp"
#include "HtttRequestHeaders.hpp"
#include "HtttRequestStatusLine.hpp"

namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{

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
friend MAIN_NAMESPACE::HttpRequest;
public:
    typedef size_t                      SizeType;
    typedef char*                       BufferType;
    typedef std::vector<BufferType>     BufferContainerType;
    typedef HttpRequestParserException  ExceptionType;

    ~HttpRequestParser();

    void parseHttpRequest(const BufferContainerType& buffer, int bufferSize, int lastSize);
    void clear();

    const HttpRequestHeaders& getHeaders() const;
    const HttpRequestStatusLine& getStatusLine() const;

private:
    HttpRequestHeaders httpRequestHeaders_;
    HttpRequestStatusLine httpRequestStatusLine_;

    HttpRequestParser();
    HttpRequestParser(const HttpRequestParser& other);

    HttpRequestParser& operator=(const HttpRequestParser& other);

    std::vector<std::string> split_(const std::string& str  , char delimiter);
    int find_(char* arr, int startPoint, int size, char c);

    std::vector<std::string> parseBuffer_(const BufferContainerType& buffer, int bufferSize, int lastSize);
    void parseStatusLine(const std::string& line);

};

}
