#include "../../include/http_request_parser/HtttRequestHeaders.hpp"

namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{

HttpRequestHeaders::HttpRequestHeaders(){

}
HttpRequestHeaders::HttpRequestHeaders(const HttpRequestHeaders& other){
    (void)other;
}
HttpRequestHeaders::~HttpRequestHeaders(){

}

HttpRequestHeaders& HttpRequestHeaders::operator=(const HttpRequestHeaders& other){
    (void)other;
    return *this;
}

}