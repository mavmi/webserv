#include "../../include/utils/httpHeadersAbstractParent.hpp"

namespace MAIN_NAMESPACE::UTILS_NAMESPACE{

HttpHeadersAbstractParent::HttpHeadersAbstractParent(){
    httpVersion_ = 0.9;
}
HttpHeadersAbstractParent::HttpHeadersAbstractParent(const HttpHeadersAbstractParent& other){
    httpVersion_ = other.httpVersion_;
}
HttpHeadersAbstractParent::~HttpHeadersAbstractParent(){}

HttpHeadersAbstractParent& HttpHeadersAbstractParent::operator=(const HttpHeadersAbstractParent& other){
    httpVersion_ = other.httpVersion_;
    return *this;
}

void HttpHeadersAbstractParent::setVersion(HTTP_VERSION_TYPE httpVersion){
    httpVersion_ = httpVersion;
}

}
