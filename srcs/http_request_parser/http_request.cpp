#include "../../include/http_request_parser/http_request.hpp"

namespace MAIN_NAMESPACE{

HttpRequest::HttpRequest(){}
HttpRequest::HttpRequest(const HttpRequest::BufferContainerType& buffer, int bufferSize, int lastSize){
    httpRequestParser_.parseHttpRequest(buffer, bufferSize, lastSize);
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

HttpRequest HttpRequest::parseHttpRequest(const HttpRequest::BufferContainerType& buffer, int bufferSize, int lastSize){
    return HttpRequest(buffer, bufferSize, lastSize);
}
const HTTP_REQUEST_PARS_NAMESPACE::HttpRequestParser& HttpRequest::getHttpRequest() const{
    return httpRequestParser_;
}

}
