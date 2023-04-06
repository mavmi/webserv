#include "../../includes/http_headers/response_status_line.hpp"

namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{
HttpResponseStatusLineException::HttpResponseStatusLineException(const char* msg) : Exception(msg){}
HttpResponseStatusLineException::HttpResponseStatusLineException(const std::string& msg) : Exception(msg){}
HttpResponseStatusLineException::HttpResponseStatusLineException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpResponseStatusLineException::HttpResponseStatusLineException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpResponseStatusLineException::HttpResponseStatusLineException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
HttpResponseStatusLineException::HttpResponseStatusLineException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string HttpResponseStatusLineException::output_() const {
    return "HTTP_RESPONSE_STATUS_LINE_EXCEPTION: " + msg_;
}
}
}


namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{
HttpResponseStatusLine::HttpResponseStatusLine(){
    isDone_ = false;
}
HttpResponseStatusLine::HttpResponseStatusLine(const HttpResponseStatusLine& other)
    : StatusLineAbstractParent(other){
    copyData_(other);
}
HttpResponseStatusLine::~HttpResponseStatusLine(){
    deleteData_();
}

HttpResponseStatusLine& HttpResponseStatusLine::operator=(const HttpResponseStatusLine& other){
    deleteData_();
    copyData_(other);
    return *this;
}

void HttpResponseStatusLine::setStatusCode(std::string statusCode){
    throwOnDone_();
    statusCode_.set(statusCode);
}
std::string& HttpResponseStatusLine::getStatusCode(){
    HANDLE_EXC_BEGIN
        return statusCode_.get();
    HANDLE_EXC_END
}
const std::string& HttpResponseStatusLine::getStatusCode() const{
    HANDLE_EXC_BEGIN
        return statusCode_.get();
    HANDLE_EXC_END
}

void HttpResponseStatusLine::setMessage(std::string message){
    throwOnDone_();
    message_.set(message);
}
std::string& HttpResponseStatusLine::getMessage(){
    HANDLE_EXC_BEGIN
        return message_.get();
    HANDLE_EXC_END
}
const std::string& HttpResponseStatusLine::getMessage() const{
    HANDLE_EXC_BEGIN
        return message_.get();
    HANDLE_EXC_END
}

void HttpResponseStatusLine::deleteData_(){
    httpVersion_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_VERSION>();
    statusCode_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    message_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
}
void HttpResponseStatusLine::copyData_(const MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent& o){
    const HttpResponseStatusLine& other = dynamic_cast<const HttpResponseStatusLine&>(o);

    httpVersion_ = other.httpVersion_;
    statusCode_ = other.statusCode_;
    message_ = other.message_;
}
void HttpResponseStatusLine::checkValidity_() const{
    if (!httpVersion_.isSet()) throw ExceptionType("HTTP version is not set", EXC_ARGS);
    if (!statusCode_.isSet()) throw ExceptionType("Status code is not set", EXC_ARGS);

    const std::string errMsg = "Status code got invalid string";
    if (statusCode_.get().size() != 3) throw ExceptionType(errMsg);
    for (size_t i = 0; i < statusCode_.get().size(); i++){
        char c = statusCode_.get().at(i); 
        if (c < '0' || c > '9') throw ExceptionType(errMsg);
    }
}
}
}
