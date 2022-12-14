#include "../../include/http_request_parser/HttpRequest.hpp"

namespace MAIN_NAMESPACE{

HttpRequest::HttpRequest(){

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

void HttpRequest::parseHttpRequest(const std::vector<char *>& buffer){
    (void)buffer;
}
const HTTP_REQUEST_PARS_NAMESPACE::HttpRequestParser& HttpRequest::getHttpRequest() const{
    return httpRequestParser_;
}

}
