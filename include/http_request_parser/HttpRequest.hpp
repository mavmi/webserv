#pragma once

#include "HttpRequestParser.hpp"
#include "utils.hpp"

namespace MAIN_NAMESPACE{

class HttpRequest{
public:
    typedef HTTP_REQUEST_PARS_NAMESPACE::HttpRequestParser::BufferContainerType     BufferContainerType;

    HttpRequest();
    HttpRequest(const BufferContainerType& buffer);
    HttpRequest(const HttpRequest& other);

    ~HttpRequest();

    HttpRequest& operator=(const HttpRequest& other);
    const HTTP_REQUEST_PARS_NAMESPACE::HttpRequestParser& operator->();

    static HttpRequest parseHttpRequest(const BufferContainerType& buffer);
    const HTTP_REQUEST_PARS_NAMESPACE::HttpRequestParser& getHttpRequest() const;

private:
    HTTP_REQUEST_PARS_NAMESPACE::HttpRequestParser httpRequestParser_;

};

}
