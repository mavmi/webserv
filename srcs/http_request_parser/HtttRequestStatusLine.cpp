#include "../../include/http_request_parser/HtttRequestStatusLine.hpp"

namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{
HttpRequestStatusLineException::HttpRequestStatusLineException(const char* msg) : Exception(msg){}
HttpRequestStatusLineException::HttpRequestStatusLineException(const std::string& msg) : Exception(msg){}
HttpRequestStatusLineException::HttpRequestStatusLineException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpRequestStatusLineException::HttpRequestStatusLineException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpRequestStatusLineException::HttpRequestStatusLineException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
HttpRequestStatusLineException::HttpRequestStatusLineException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string HttpRequestStatusLineException::output_() const {
    return "HTTP_REQUEST_STATUS_LINE_EXCEPTION: " + msg_;
}
}


namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{
HttpRequestStatusLine::HttpRequestStatusLine(){

}
HttpRequestStatusLine::HttpRequestStatusLine(const HttpRequestStatusLine& other){
    (void)other;
}
HttpRequestStatusLine::~HttpRequestStatusLine(){

}

HttpRequestStatusLine& HttpRequestStatusLine::operator=(const HttpRequestStatusLine& other){
    (void)other;
    return *this;    
}
}
