#include "../../include/http_request_parser/HtttRequestStatusLine.hpp"

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
