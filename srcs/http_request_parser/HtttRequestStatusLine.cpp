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
    isDone_ = false;
}
HttpRequestStatusLine::HttpRequestStatusLine(const HttpRequestStatusLine& other){
    isDone_ = other.isDone_;
    method_ = other.method_;
    url_ = other.url_;
    httpVersion_ = other.httpVersion_;
}
HttpRequestStatusLine::~HttpRequestStatusLine(){

}

HttpRequestStatusLine& HttpRequestStatusLine::operator=(const HttpRequestStatusLine& other){
    isDone_ = other.isDone_;
    method_ = other.method_;
    url_ = other.url_;
    httpVersion_ = other.httpVersion_;
    return *this;    
}

void HttpRequestStatusLine::setMethod(METHOD method){
    throwOnDone_();
    method_.set(method);
}
HttpRequestStatusLine::METHOD& HttpRequestStatusLine::getMethod(){
    HANDLE_EXC_BEGIN
        return method_.get();
    HANDLE_EXC_END
}
const HttpRequestStatusLine::METHOD& HttpRequestStatusLine::getMethod() const{
    HANDLE_EXC_BEGIN
        return method_.get();
    HANDLE_EXC_END
}

void HttpRequestStatusLine::setUrl(const URL_TYPE& url){
    throwOnDone_();
    url_.set(url);
}
HttpRequestStatusLine::URL_TYPE& HttpRequestStatusLine::getUrl(){
    HANDLE_EXC_BEGIN
        return url_.get();
    HANDLE_EXC_END
}
const HttpRequestStatusLine::URL_TYPE& HttpRequestStatusLine::getUrl() const{
    HANDLE_EXC_BEGIN
        return url_.get();
    HANDLE_EXC_END
}

void HttpRequestStatusLine::setHttpVersion(HTTP_VERSION_TYPE httpVersion){
    throwOnDone_();
    httpVersion_.set(httpVersion);
}
HttpRequestStatusLine::HTTP_VERSION_TYPE& HttpRequestStatusLine::getHttpVersion(){
    HANDLE_EXC_BEGIN
        return httpVersion_.get();
    HANDLE_EXC_END
}
const HttpRequestStatusLine::HTTP_VERSION_TYPE& HttpRequestStatusLine::getHttpVersion() const{
    HANDLE_EXC_BEGIN
        return httpVersion_.get();
    HANDLE_EXC_END
}

void HttpRequestStatusLine::checkValidity_() const{
    if (!method_.isSet()) throw ExceptionType("Method is not set up", EXC_ARGS);
    if (!url_.isSet()) throw ExceptionType("URL is not set up", EXC_ARGS);
    if (!httpVersion_.isSet()) throw ExceptionType("HTTP version is not set up", EXC_ARGS);
}
void HttpRequestStatusLine::throwOnDone_() const{
    if (isDone_) throw ExceptionType("Status line is done. You cannot change it anymore.", EXC_ARGS);
}
}
