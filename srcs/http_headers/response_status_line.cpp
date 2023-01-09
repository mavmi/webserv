#include "../../include/http_headers/response_status_line.hpp"

namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{
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


namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{
HttpResponseStatusLine::HttpResponseStatusLine(){
    isDone_ = false;
}
HttpResponseStatusLine::HttpResponseStatusLine(const HttpResponseStatusLine& other){
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

void HttpResponseStatusLine::setHttpVersion(HttpVersionType httpVersion){
    throwOnDone_();
    httpVersion_.set(httpVersion);
}
HttpResponseStatusLine::HttpVersionType& HttpResponseStatusLine::getHttpVersion(){
    HANDLE_EXC_BEGIN
        return httpVersion_.get();
    HANDLE_EXC_END
}
const HttpResponseStatusLine::HttpVersionType& HttpResponseStatusLine::getHttpVersion() const{
    HANDLE_EXC_BEGIN
        return httpVersion_.get();
    HANDLE_EXC_END
}

void HttpResponseStatusLine::setStatusCode(StatusCodeType statusCode){
    throwOnDone_();
    statusCode_.set(statusCode);
}
HttpResponseStatusLine::StatusCodeType& HttpResponseStatusLine::getStatusCode(){
    HANDLE_EXC_BEGIN
        return statusCode_.get();
    HANDLE_EXC_END
}
const HttpResponseStatusLine::StatusCodeType& HttpResponseStatusLine::getStatusCode() const{
    HANDLE_EXC_BEGIN
        return statusCode_.get();
    HANDLE_EXC_END
}

void HttpResponseStatusLine::setMessage(MessageType message){
    throwOnDone_();
    message_.set(message);
}
HttpResponseStatusLine::MessageType& HttpResponseStatusLine::getMessage(){
    HANDLE_EXC_BEGIN
        return message_.get();
    HANDLE_EXC_END
}
const HttpResponseStatusLine::MessageType& HttpResponseStatusLine::getMessage() const{
    HANDLE_EXC_BEGIN
        return message_.get();
    HANDLE_EXC_END
}

void HttpResponseStatusLine::deleteData_(){
    httpVersion_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<HttpVersionType>();
    statusCode_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<StatusCodeType>();
    message_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<MessageType>();
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
void HttpResponseStatusLine::throwOnDone_() const{
    if (isDone_) throw ExceptionType("Status line is done. You cannot change it anymore.", EXC_ARGS);
}
}
