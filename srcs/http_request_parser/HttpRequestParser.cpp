#include "../../include/http_request_parser/HttpRequestParser.hpp"

namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{
HttpRequestParserException::HttpRequestParserException(const char* msg) : Exception(msg){}
HttpRequestParserException::HttpRequestParserException(const std::string& msg) : Exception(msg){}
HttpRequestParserException::HttpRequestParserException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpRequestParserException::HttpRequestParserException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpRequestParserException::HttpRequestParserException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
HttpRequestParserException::HttpRequestParserException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string HttpRequestParserException::output_() const {
    return "HTTP_REQUEST_PARSER_EXCEPTION: " + msg_;
}
}


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

void HttpRequestParser::parseHttpRequest(const HttpRequestParser::BufferContainerType& buffer){
    (void)buffer;
}
void HttpRequestParser::clear(){

}
}
