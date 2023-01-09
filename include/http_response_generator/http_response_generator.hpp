#pragma once

#include "utils.hpp"
#include "../http_headers/response_status_line.hpp"
#include "../http_headers/general_headers.hpp"
#include "../http_headers/response_headers.hpp"

namespace MAIN_NAMESPACE::HTTP_RESPONSE_GENER_NAMESPACE{

class HttpResponseGeneratorException : public MAIN_NAMESPACE::UTILS_NAMESPACE::Exception {
public:
    HttpResponseGeneratorException(const char* msg);
    HttpResponseGeneratorException(const std::string& msg);

    HttpResponseGeneratorException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    HttpResponseGeneratorException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    HttpResponseGeneratorException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    HttpResponseGeneratorException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    virtual std::string output_() const;

};


class HttpResponseGenerator{
public:
    typedef char*                           BufferType;
    typedef std::vector<BufferType>         BufferContainerType;
    typedef HttpResponseGeneratorException  ExceptionType;
    
    struct BytesContainer{
        BytesContainer(){
            container = BufferContainerType();
            bufferSize = 64;
            lastSize = 0;
        }
        BytesContainer(const BytesContainer& other);
        ~BytesContainer();

        BytesContainer& operator=(const BytesContainer& other);

        BufferContainerType container;
        size_t bufferSize;
        size_t lastSize;
    };

    HttpResponseGenerator();
    HttpResponseGenerator(const HttpResponseGenerator& other);
    ~HttpResponseGenerator();

    HttpResponseGenerator& operator=(const HttpResponseGenerator& other);

    MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseStatusLine& getStatusLine();
    const MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseStatusLine& getStatusLine() const;

    MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeaders& getHeaders();
    const MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeaders& getHeaders() const;

    std::vector<std::string>& getMessage();
    const std::vector<std::string>& getMessage() const;

    BytesContainer toBytes();

private:
    MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseStatusLine responseStatusLine_;
    MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeaders responseHeaders_;
    std::vector<std::string> message_;

};
    
}
