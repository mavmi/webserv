#include "../../include/http_headers/status_line_abstract_parent.hpp"

namespace MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE{
StatusLineAbstractParentException::StatusLineAbstractParentException(const char* msg) : Exception(msg){}
StatusLineAbstractParentException::StatusLineAbstractParentException(const std::string& msg) : Exception(msg){}
StatusLineAbstractParentException::StatusLineAbstractParentException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
StatusLineAbstractParentException::StatusLineAbstractParentException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
StatusLineAbstractParentException::StatusLineAbstractParentException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
StatusLineAbstractParentException::StatusLineAbstractParentException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string StatusLineAbstractParentException::output_() const {
    return "HTTP_STATUS_LINE_ABSTRACT_PARENT_EXCEPTION: " + msg_;
}
}


namespace MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE{
StatusLineAbstractParent::StatusLineAbstractParent(){
    
}
StatusLineAbstractParent::StatusLineAbstractParent(const StatusLineAbstractParent& other){
    copyData_(other);
}
StatusLineAbstractParent::~StatusLineAbstractParent(){
    deleteData_();
}

StatusLineAbstractParent& StatusLineAbstractParent::operator=(const StatusLineAbstractParent& other){
    deleteData_();
    copyData_(other);
    return *this;    
}

void StatusLineAbstractParent::setHttpVersion(HttpVersionType httpVersion){
    throwOnDone_();
    httpVersion_.set(httpVersion);
}
StatusLineAbstractParent::HttpVersionType& StatusLineAbstractParent::getHttpVersion(){
    HANDLE_EXC_BEGIN
        return httpVersion_.get();
    HANDLE_EXC_END
}
const StatusLineAbstractParent::HttpVersionType& StatusLineAbstractParent::getHttpVersion() const{
    HANDLE_EXC_BEGIN
        return httpVersion_.get();
    HANDLE_EXC_END
}

void StatusLineAbstractParent::deleteData_(){
    httpVersion_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<HttpVersionType>();
}
void StatusLineAbstractParent::copyData_(const MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent& o){
    const StatusLineAbstractParent& other = dynamic_cast<const StatusLineAbstractParent&>(o);

    httpVersion_ = other.httpVersion_;
}
void StatusLineAbstractParent::checkValidity_() const{
    if (!httpVersion_.isSet()) throw ExceptionType("HTTP version is not set", EXC_ARGS);
}
void StatusLineAbstractParent::throwOnDone_() const{
    if (isDone_) throw ExceptionType("Status line is done. You cannot change it anymore.", EXC_ARGS);
}
}
