#pragma once

#include "HttpRequestParser.hpp"
#include "utils.hpp"

namespace MAIN_NAMESPACE{

class HttpRequest{
public:
    HttpRequest();
    HttpRequest(const HttpRequest& other);
    ~HttpRequest();

    HttpRequest& operator=(const HttpRequest& other);

    void parseHttpRequest(const std::vector<char *>& buffer);
    const HTTP_REQUEST_PARS_NAMESPACE::HttpRequestParser& getHttpRequest() const;

private:
    HTTP_REQUEST_PARS_NAMESPACE::HttpRequestParser httpRequestParser_;

};

}
