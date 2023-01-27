#include "../../include/http_headers/request_status_line.hpp"

namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{
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
}


namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{
HttpRequestStatusLine::HttpRequestStatusLine(){
    isDone_ = false;
}
HttpRequestStatusLine::HttpRequestStatusLine(const HttpRequestStatusLine& other)
    : StatusLineAbstractParent(other) {
    copyData_(other);
}
HttpRequestStatusLine::~HttpRequestStatusLine(){
    deleteData_();
}

HttpRequestStatusLine& HttpRequestStatusLine::operator=(const HttpRequestStatusLine& other){
    deleteData_();
    copyData_(other);
    return *this;    
}

void HttpRequestStatusLine::setMethod(MethodType method){
    throwOnDone_();
    method_.set(method);
}
HttpRequestStatusLine::MethodType& HttpRequestStatusLine::getMethod(){
    HANDLE_EXC_BEGIN
        return method_.get();
    HANDLE_EXC_END
}
const HttpRequestStatusLine::MethodType& HttpRequestStatusLine::getMethod() const{
    HANDLE_EXC_BEGIN
        return method_.get();
    HANDLE_EXC_END
}

void HttpRequestStatusLine::setUrl(const UrlType& url){
    throwOnDone_();
    url_.set(url);
}
HttpRequestStatusLine::UrlType& HttpRequestStatusLine::getUrl(){
    HANDLE_EXC_BEGIN
        return url_.get();
    HANDLE_EXC_END
}
const HttpRequestStatusLine::UrlType& HttpRequestStatusLine::getUrl() const{
    HANDLE_EXC_BEGIN
        return url_.get();
    HANDLE_EXC_END
}

void HttpRequestStatusLine::deleteData_(){
    isDone_ = false;
    method_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<MethodType>();
    url_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<UrlType>();
    httpVersion_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<HttpVersionType>();
}
void HttpRequestStatusLine::copyData_(const MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent& o){
    const HttpRequestStatusLine& other = dynamic_cast<const HttpRequestStatusLine&>(o);

    isDone_ = other.isDone_;
    method_ = other.method_;
    url_ = other.url_;
    httpVersion_ = other.httpVersion_;
}
void HttpRequestStatusLine::checkValidity_() const{
    if (!method_.isSet()) throw ExceptionType("Method is not set up", EXC_ARGS);
    if (!url_.isSet()) throw ExceptionType("URL is not set up", EXC_ARGS);
    if (!httpVersion_.isSet()) throw ExceptionType("HTTP version is not set up", EXC_ARGS);
}
}
}
