#pragma once

#include "utils.hpp"
#include "../http_request_parser/HtttRequestStatusLine.hpp"

namespace MAIN_NAMESPACE::UTILS_NAMESPACE{

class HttpHeadersAbstractParent{
public:
    typedef MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE::HttpRequestStatusLine::HTTP_VERSION_TYPE   HTTP_VERSION_TYPE;
    
    void setVersion(HTTP_VERSION_TYPE httpVersionType);

protected:
    HTTP_VERSION_TYPE httpVersion_;

    HttpHeadersAbstractParent();
    HttpHeadersAbstractParent(const HttpHeadersAbstractParent& other);
    ~HttpHeadersAbstractParent();

    HttpHeadersAbstractParent& operator=(const HttpHeadersAbstractParent& other);

};

}
