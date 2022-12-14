#include "../../include/http_request_parser/HttpRequestParser.hpp"

namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{

HttpRequestParser::HttpRequestParser(){

}
HttpRequestParser::HttpRequestParser(const HttpRequestParser& other){
    (void)other;
}
HttpRequestParser::~HttpRequestParser(){

}

HttpRequestParser& HttpRequestParser::operator=(const HttpRequestParser& other){
    (void)other;
    return *this;
}

void HttpRequestParser::parseHttpRequest(const std::vector<char *>& buffer){
    (void)buffer;
}
void HttpRequestParser::clear(){

}

}
