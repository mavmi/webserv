#include "../../include/http_response_generator/http_response_generator.hpp"

namespace MAIN_NAMESPACE::HTTP_RESPONSE_GENER_NAMESPACE{
HttpResponseGeneratorException::HttpResponseGeneratorException(const char* msg) : Exception(msg){}
HttpResponseGeneratorException::HttpResponseGeneratorException(const std::string& msg) : Exception(msg){}
HttpResponseGeneratorException::HttpResponseGeneratorException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpResponseGeneratorException::HttpResponseGeneratorException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpResponseGeneratorException::HttpResponseGeneratorException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
HttpResponseGeneratorException::HttpResponseGeneratorException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string HttpResponseGeneratorException::output_() const {
    return "HTTP_RESPONSE_GENERATOR_EXCEPTION: " + msg_;
}
}


namespace MAIN_NAMESPACE::HTTP_RESPONSE_GENER_NAMESPACE{
HttpResponseGenerator::HttpResponseGenerator()
    : responseStatusLine_(MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseStatusLine()),
        responseHeaders_(MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeaders(responseStatusLine_)),
        message_(std::vector<std::string>()) {

}
HttpResponseGenerator::HttpResponseGenerator(const HttpResponseGenerator& other)
    : responseStatusLine_(other.responseStatusLine_),
        responseHeaders_(other.responseHeaders_),
        message_(other.message_){

}
HttpResponseGenerator::~HttpResponseGenerator(){

}

HttpResponseGenerator& HttpResponseGenerator::operator=(const HttpResponseGenerator& other){
    responseStatusLine_ = other.responseStatusLine_;
    responseHeaders_ = other.responseHeaders_;
    message_ = other.message_;
    return *this;
}

MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseStatusLine& HttpResponseGenerator::getStatusLine(){
    return responseStatusLine_;
}
const MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseStatusLine& HttpResponseGenerator::getStatusLine() const{
    return responseStatusLine_;
}

MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeaders& HttpResponseGenerator::getHeaders(){
    return responseHeaders_;
}
const MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeaders& HttpResponseGenerator::getHeaders() const{
    return responseHeaders_;
}

std::vector<std::string>& HttpResponseGenerator::getMessage(){
    return message_;
}
const std::vector<std::string>& HttpResponseGenerator::getMessage() const{
    return message_;
}

HttpResponseGenerator::BytesContainer HttpResponseGenerator::toBytes(){
    responseStatusLine_.done();
    responseHeaders_.done();
    
    BytesContainer result;

    // Status line
    {
        std::string statusLineStr;

        MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_VERSION httpVersion = responseStatusLine_.getHttpVersion();
        if (httpVersion == MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_0_9){
            statusLineStr += "HTTP/0.9";
        } else if (httpVersion == MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0){
            statusLineStr += "HTTP/1.0";
        } else if (httpVersion == MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1){
            statusLineStr += "HTTP/1.1";
        } else if (httpVersion == MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1v2){
            statusLineStr += "HTTP/1.1v2";
        } else if (httpVersion == MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_AUTH){
            statusLineStr += "HTTP-Auth";
        } else if (httpVersion == MAIN_NAMESPACE::UTILS_NAMESPACE::MIME){
            statusLineStr += "MIME";
        } else if (httpVersion == MAIN_NAMESPACE::UTILS_NAMESPACE::MD5H){
            statusLineStr += "MD5H";
        } else if (httpVersion == MAIN_NAMESPACE::UTILS_NAMESPACE::CDH){
            statusLineStr += "CDH";
        }

        statusLineStr += " ";
        statusLineStr += responseStatusLine_.getStatusCode();

        try {
            statusLineStr += responseStatusLine_.getMessage();
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseStatusLineException&){

        }

        size_t begin = 0, end = 0;
        while (true){
            end = (begin + result.bufferSize <= statusLineStr.size()) ? begin + result.bufferSize : statusLineStr.size();
            size_t size = end - begin;
            result.container.push_back(new char[size]);
            for (size_t i = 0, strIter = begin; i < size; i++, strIter++){
                result.container.back()[i] = statusLineStr[strIter];
            }
            if (end == statusLineStr.size()){
                result.lastSize = size;
                break;
            }
            begin = end;
        }
    }

    // Headers
    {
        // TO DO
    }

    // Message
    {
        // TO DO
    }

    return result;
}
}
