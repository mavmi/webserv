#pragma once

#include <vector>
#include <stddef.h>

#include "utils.hpp"
#include "HtttRequestHeaders.hpp"
#include "HtttRequestStatusLine.hpp"

namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{

class HttpRequestParser{
friend MAIN_NAMESPACE::HttpRequest;
public:
    typedef size_t      SizeType;
    typedef char*       BufferType;

    ~HttpRequestParser();

    void parseHttpRequest(const std::vector<char *>& buffer);

    void clear();

private:
    HttpRequestHeaders httpRequestHeaders_;
    HttpRequestStatusLine httpRequestStatusLine_;

    HttpRequestParser();
    HttpRequestParser(const HttpRequestParser& other);

    HttpRequestParser& operator=(const HttpRequestParser& other);

};

}
