#include "../../includes/http_request_parser/http_request.hpp"

namespace MAIN_NAMESPACE{
namespace HTTP_REQUEST_PARS_NAMESPACE{

HttpRequest::HttpRequest()
    : httpRequestStatusLine_(MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpRequestStatusLine()),
        httpGeneralHeaders_(MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeaders(httpRequestStatusLine_)),
        httpRequestHeaders_(MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpRequestHeaders(httpRequestStatusLine_)),
        httpRequestContent_(std::vector<std::string>()){

}
HttpRequest::HttpRequest(const HttpRequest& other)
    : httpRequestStatusLine_(other.httpRequestStatusLine_),
        httpGeneralHeaders_(MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeaders(httpRequestStatusLine_)),
        httpRequestHeaders_(MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpRequestHeaders(httpRequestStatusLine_)),
        httpRequestContent_(std::vector<std::string>()) {
    
}

HttpRequest::~HttpRequest(){}

HttpRequest& HttpRequest::operator=(const HttpRequest& other){
    httpRequestStatusLine_ = other.httpRequestStatusLine_;
    httpGeneralHeaders_ = other.httpGeneralHeaders_;
    httpRequestHeaders_ = other.httpRequestHeaders_;
    httpRequestContent_ = other.httpRequestContent_;
    return *this;
}

MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpRequestStatusLine& HttpRequest::getStatusLine(){
    return httpRequestStatusLine_;
}
const MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpRequestStatusLine& HttpRequest::getStatusLine() const{
    return httpRequestStatusLine_;
}

MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeaders& HttpRequest::getGeneralHeaders(){
    return httpGeneralHeaders_;
}
const MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeaders& HttpRequest::getGeneralHeaders() const{
    return httpGeneralHeaders_;
}

MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpRequestHeaders& HttpRequest::getRequestHeaders(){
    return httpRequestHeaders_;
}
const MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpRequestHeaders& HttpRequest::getRequestHeaders() const{
    return httpRequestHeaders_;
}

std::vector<std::string>& HttpRequest::getRequestContent(){
    return httpRequestContent_;
}
const std::vector<std::string>& HttpRequest::getRequestContent() const{
    return httpRequestContent_;
}

}
}
