#include "../../include/http_request_parser/HttpRequest.hpp"

namespace MAIN_NAMESPACE{

HttpRequest::HttpRequest(){

}
HttpRequest::HttpRequest(const HttpRequest::BufferContainerType& buffer){
    (void)buffer;
}
HttpRequest::HttpRequest(const HttpRequest& other){
    (void)other;
}

HttpRequest::~HttpRequest(){

}

HttpRequest& HttpRequest::operator=(const HttpRequest& other){
    (void)other;
    return *this;
}
const HTTP_REQUEST_PARS_NAMESPACE::HttpRequestParser& HttpRequest::operator->(){
    return httpRequestParser_;
}

HttpRequest HttpRequest::parseHttpRequest(const HttpRequest::BufferContainerType& buffer){
    (void)buffer;
    return HttpRequest();
}
const HTTP_REQUEST_PARS_NAMESPACE::HttpRequestParser& HttpRequest::getHttpRequest() const{
    return httpRequestParser_;
}

}
