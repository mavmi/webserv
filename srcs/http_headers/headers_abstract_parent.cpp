#include "../../includes/http_headers/headers_abstract_parent.hpp"

namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{
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
    return "HTTP_ABSTRACT_HEADERS_PARENT_EXCEPTION: " + msg_;
}
}
}


namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{
HttpHeadersAbstractParent::HttpHeadersAbstractParent(const StatusLineAbstractParent& statusLine)
    : statusLine_(statusLine) {
    
}
HttpHeadersAbstractParent::HttpHeadersAbstractParent(const HttpHeadersAbstractParent& other)
    : statusLine_(other.statusLine_) {
    
}
HttpHeadersAbstractParent::~HttpHeadersAbstractParent(){}

HttpHeadersAbstractParent& HttpHeadersAbstractParent::operator=(const HttpHeadersAbstractParent&){
    return *this;
}

MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_VERSION HttpHeadersAbstractParent::getHttpVersion_() const{
    return statusLine_.getHttpVersion();
}
void HttpHeadersAbstractParent::checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_VERSION version){
    const std::string excMsg = "Invalid HTTP ver for current header";
    
    if ((version == MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_AUTH || version == MAIN_NAMESPACE::UTILS_NAMESPACE::MIME ||
            version == MAIN_NAMESPACE::UTILS_NAMESPACE::MD5H || version == MAIN_NAMESPACE::UTILS_NAMESPACE::CDH)){
        if (version != getHttpVersion_()){
            throw ExceptionType(excMsg);
        }
    } else {
        if (version > getHttpVersion_()){
            throw ExceptionType(excMsg);
        }
    }
}

std::string HttpHeadersAbstractParent::generateDate_(std::tm* time) const {
    std::string result;

    switch (time->tm_wday){
        case 0:
            result += "Sun";
            break;
        case 1:
            result += "Mon";
            break;
        case 2:
            result += "Tues";
            break;
        case 3:
            result += "Wed";
            break;
        case 4:
            result += "Thurs";
            break;
        case 5:
            result += "Fri";
            break;
        case 6:
            result += "Sat";
            break;
    }
    result += ", ";

    result += MAIN_NAMESPACE::UTILS_NAMESPACE::utilsNumToString(time->tm_mday);
    result += " ";

    switch (time->tm_mon){
        case 0:
            result += "Jan";
            break;
        case 1:
            result += "Feb";
            break;
        case 2:
            result += "Mar";
            break;
        case 3:
            result += "Apr";
            break;
        case 4:
            result += "May";
            break;
        case 5:
            result += "Jun";
            break;
        case 6:
            result += "Jul";
            break;
        case 7:
            result += "Aug";
            break;
        case 8:
            result += "Sep";
            break;
        case 9:
            result += "Oct";
            break;
        case 10:
            result += "Nov";
            break;
        case 11:
            result += "Dec";
            break;
    }
    result += " ";

    result += MAIN_NAMESPACE::UTILS_NAMESPACE::utilsNumToString(1900 + time->tm_year);
    result += " ";
    
    int tmp;

    tmp = time->tm_hour;
    if (tmp < 10) result += "0";
    result += MAIN_NAMESPACE::UTILS_NAMESPACE::utilsNumToString(tmp);
    result += ":";

    tmp = time->tm_min;
    if (tmp < 10) result += "0";
    result += MAIN_NAMESPACE::UTILS_NAMESPACE::utilsNumToString(tmp);
    result += ":";

    tmp = time->tm_sec;
    if (tmp < 10) result += "0";
    result += MAIN_NAMESPACE::UTILS_NAMESPACE::utilsNumToString(tmp);
    result += " GMT";

    return result;
}
}
}
