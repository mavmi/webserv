#include "../../include/http_request_parser/HtttRequestHeaders.hpp"

namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{
HttpRequestHeadersException::HttpRequestHeadersException(const char* msg) : Exception(msg){}
HttpRequestHeadersException::HttpRequestHeadersException(const std::string& msg) : Exception(msg){}
HttpRequestHeadersException::HttpRequestHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpRequestHeadersException::HttpRequestHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpRequestHeadersException::HttpRequestHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
HttpRequestHeadersException::HttpRequestHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string HttpRequestHeadersException::output_() const {
    return "HTTP_REQUEST_HEADERS_EXCEPTION: " + msg_;
}
}


namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{
HttpRequestHeaders::HttpRequestHeaders(){

}
HttpRequestHeaders::HttpRequestHeaders(const HttpRequestHeaders& other)
    : ParserAbstractParent(other), HttpHeadersAbstractParent(other) {
    copyData_(other);
}
HttpRequestHeaders::~HttpRequestHeaders(){
    deleteData_();
}

HttpRequestHeaders& HttpRequestHeaders::operator=(const HttpRequestHeaders& other){
    deleteData_();
    copyData_(other);
    return *this;
}

void HttpRequestHeaders::deleteData_(){

}
void HttpRequestHeaders::copyData_(const ParserAbstractParent& o){
    const HttpRequestHeaders& other = dynamic_cast<const HttpRequestHeaders&>(o);
    (void)other;
}
void HttpRequestHeaders::checkValidity_() const{

}
void HttpRequestHeaders::throwOnDone_() const{
    if (isDone_) throw ExceptionType("Request headers are done. You cannot change it anymore");
}
}