#pragma once

#include <fstream>
#include <sys/stat.h>

#include "utils.hpp"
#include "../http_headers/response_status_line.hpp"
#include "../http_headers/general_headers.hpp"
#include "../http_headers/response_headers.hpp"

namespace MAIN_NAMESPACE{
class HttpResponseException : public MAIN_NAMESPACE::UTILS_NAMESPACE::Exception {
public:
    HttpResponseException(const char* msg);
    HttpResponseException(const std::string& msg);

    HttpResponseException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    HttpResponseException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    HttpResponseException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    HttpResponseException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    virtual std::string output_() const;

};
}


namespace MAIN_NAMESPACE{
class HttpResponse{
public:
    typedef HttpResponseException  ExceptionType;

    HttpResponse();
    HttpResponse(const HttpResponse& other);
    ~HttpResponse();

    HttpResponse& operator=(const HttpResponse& other);

    MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseStatusLine& getStatusLine();
    const MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseStatusLine& getStatusLine() const;

    MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeaders& getGeneralHeaders();
    const MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeaders& getGeneralHeaders() const;

    MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeaders& getResponseHeaders();
    const MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeaders& getResponseHeaders() const;

    std::vector<char>& getMessage();
    const std::vector<char>& getMessage() const;

    MAIN_NAMESPACE::UTILS_NAMESPACE::BytesContainer toBytes();

    void setDate();
    void setRetryAfter();
    void setStatusLine(
                MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_VERSION httpVersion,
                std::string statusCode,
                std::string message
            );
    bool setupFile(const std::string& filePath, const std::string& errFilePath);

private:
    MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseStatusLine responseStatusLine_;
    MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeaders generalHeaders_;
    MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeaders responseHeaders_;
    std::vector<char> message_;

    bool setupFileOnError();
    std::string parseFileSignature_(const std::string& fileName) const;
    std::string parseFileExtension_(const std::string& fileName) const;

};
}
