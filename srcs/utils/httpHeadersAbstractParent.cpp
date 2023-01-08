#include "../../include/utils/httpHeadersAbstractParent.hpp"

namespace MAIN_NAMESPACE::UTILS_NAMESPACE{
HttpHeadersAbstractParentException::HttpHeadersAbstractParentException(const char* msg) : Exception(msg){}
HttpHeadersAbstractParentException::HttpHeadersAbstractParentException(const std::string& msg) : Exception(msg){}
HttpHeadersAbstractParentException::HttpHeadersAbstractParentException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpHeadersAbstractParentException::HttpHeadersAbstractParentException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpHeadersAbstractParentException::HttpHeadersAbstractParentException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
HttpHeadersAbstractParentException::HttpHeadersAbstractParentException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string HttpHeadersAbstractParentException::output_() const {
    return "HTTP_REQUEST_HEADERS_EXCEPTION: " + msg_;
}
}

namespace MAIN_NAMESPACE::UTILS_NAMESPACE{
HttpHeadersAbstractParent::HttpHeadersAbstractParent(const MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE::HttpRequestStatusLine& statusLine)
    : statusLine_(statusLine) {
    
}
HttpHeadersAbstractParent::HttpHeadersAbstractParent(const HttpHeadersAbstractParent& other)
    : statusLine_(other.statusLine_) {
    
}
HttpHeadersAbstractParent::~HttpHeadersAbstractParent(){}

HttpHeadersAbstractParent& HttpHeadersAbstractParent::operator=(const HttpHeadersAbstractParent&){
    return *this;
}

HttpHeadersAbstractParent::HttpVersionType HttpHeadersAbstractParent::getHttpVersion_() const{
    return statusLine_.getHttpVersion();
}
void HttpHeadersAbstractParent::checkVersion_(HttpVersionType version){
    using namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE;

    const std::string excMsg = "Invalid HTTP ver for current header";
    
    if ((version == HttpRequestStatusLine::HTTP_AUTH || version == HttpRequestStatusLine::MIME ||
            version == HttpRequestStatusLine::MD5H || version == HttpRequestStatusLine::CDH)){
        if (version != getHttpVersion_()){
            throw ExceptionType(excMsg);
        }
    } else {
        if (version > getHttpVersion_()){
            throw ExceptionType(excMsg);
        }
    }
}
}
