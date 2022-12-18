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
HttpRequestHeaders::HttpRequestHeaders(const HttpRequestHeaders& other){
    (void)other;
}
HttpRequestHeaders::~HttpRequestHeaders(){

}

HttpRequestHeaders& HttpRequestHeaders::operator=(const HttpRequestHeaders& other){
    (void)other;
    return *this;
}
}