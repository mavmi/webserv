#include "../../include/http_request_parser/http_request.hpp"

namespace MAIN_NAMESPACE{

HttpRequest::HttpRequest(){}
HttpRequest::HttpRequest(const MAIN_NAMESPACE::UTILS_NAMESPACE::BytesContainer& buffer){
    httpRequestParser_.parseHttpRequest(buffer);
}
HttpRequest::HttpRequest(const HttpRequest& other){
    httpRequestParser_ = other.httpRequestParser_;
}

HttpRequest::~HttpRequest(){}

HttpRequest& HttpRequest::operator=(const HttpRequest& other){
    httpRequestParser_ = other.httpRequestParser_;
    return *this;
}
const HTTP_REQUEST_PARS_NAMESPACE::HttpRequestParser& HttpRequest::operator->(){
    return httpRequestParser_;
}

HttpRequest HttpRequest::parseHttpRequest(const MAIN_NAMESPACE::UTILS_NAMESPACE::BytesContainer& buffer){
    return HttpRequest(buffer);
}
const HTTP_REQUEST_PARS_NAMESPACE::HttpRequestParser& HttpRequest::getHttpRequest() const{
    return httpRequestParser_;
}

}
