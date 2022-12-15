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

void HttpRequestParser::parseHttpRequest(const HttpRequestParser::BufferContainerType& buffer, int bufferSize, int lastSize){
    (void)buffer; (void)bufferSize; (void)lastSize;
}
void HttpRequestParser::clear(){

}

int HttpRequestParser::find_(char* arr, int startPoint, int size, char c){
    for (int i = startPoint; i < size; i++){
        if (arr[i] == c) return i;
    }
    return -1;
}
void HttpRequestParser::parseBuffer_(const BufferContainerType& buffer, int bufferSize, int lastSize){
    int startPoint;
    bool isLastFinished = true;
    const char newLine = '\n';
    std::vector<std::string> result;

    for (size_t i = 0; i < buffer.size(); i++){
        startPoint = 0;
        while (true){
            int newLinePos = find_(
                buffer[i],
                startPoint,
                i + 1 == buffer.size() ? bufferSize : lastSize,
                newLine
            );
            
            int endPoint = newLinePos == -1 ? (i + 1 == buffer.size() ? lastSize : bufferSize) : newLinePos;
            std::string substr(
                buffer[i] + startPoint,
                endPoint - startPoint
            );

            if (isLastFinished) result.push_back(substr);
            else result.back().append(substr);

            if (newLinePos == -1) {
                isLastFinished = false;
                break;
            } else {
                isLastFinished = true;
            }
            startPoint = endPoint + 1;
        }
    }
}
}
