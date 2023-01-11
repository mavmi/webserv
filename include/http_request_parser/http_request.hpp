#pragma once

#include "http_request_parser.hpp"
#include "utils.hpp"

namespace MAIN_NAMESPACE{

class HttpRequest{
public:
    typedef HTTP_REQUEST_PARS_NAMESPACE::HttpRequestParser::BufferContainerType     BufferContainerType;

    HttpRequest();
    HttpRequest(const MAIN_NAMESPACE::UTILS_NAMESPACE::BytesContainer& buffer);
    HttpRequest(const HttpRequest& other);

    ~HttpRequest();

    HttpRequest& operator=(const HttpRequest& other);
    const HTTP_REQUEST_PARS_NAMESPACE::HttpRequestParser& operator->();

    static HttpRequest parseHttpRequest(const MAIN_NAMESPACE::UTILS_NAMESPACE::BytesContainer& buffer);
    const HTTP_REQUEST_PARS_NAMESPACE::HttpRequestParser& getHttpRequest() const;

private:
    HTTP_REQUEST_PARS_NAMESPACE::HttpRequestParser httpRequestParser_;

};

}
