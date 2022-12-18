#include "../../include/http_request_parser/HttpGeneralHeaders.hpp"

namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{
HttpGeneralHeadersException::HttpGeneralHeadersException(const char* msg) : Exception(msg){}
HttpGeneralHeadersException::HttpGeneralHeadersException(const std::string& msg) : Exception(msg){}
HttpGeneralHeadersException::HttpGeneralHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpGeneralHeadersException::HttpGeneralHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpGeneralHeadersException::HttpGeneralHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
HttpGeneralHeadersException::HttpGeneralHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string HttpGeneralHeadersException::output_() const {
    return "HTTP_REQUEST_HEADERS_EXCEPTION: " + msg_;
}
}


namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{
HttpGeneralHeaders::HttpGeneralHeaders(){

}
HttpGeneralHeaders::HttpGeneralHeaders(const HttpGeneralHeaders& other)
    : ParserAbstractParent(other), HttpHeadersAbstractParent(other) {
    copyData_(other);
}
HttpGeneralHeaders::~HttpGeneralHeaders(){
    deleteData_();
}

HttpGeneralHeaders& HttpGeneralHeaders::operator=(const HttpGeneralHeaders& other){
    deleteData_();
    copyData_(other);
    return *this;
}

void HttpGeneralHeaders::deleteData_(){

}
void HttpGeneralHeaders::copyData_(const ParserAbstractParent& o){
    const HttpGeneralHeaders& other = dynamic_cast<const HttpGeneralHeaders&>(o);
    (void)other;
}
void HttpGeneralHeaders::checkValidity_() const{

}
void HttpGeneralHeaders::throwOnDone_() const{
    if (isDone_) throw ExceptionType("General headers are done. You cannot change it anymore.");
}
}
