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
HttpRequestParser::HttpRequestParser()
    : httpRequestStatusLine_(HttpRequestStatusLine()),
        httpGeneralHeaders_(HttpGeneralHeaders(httpRequestStatusLine_)),
        httpRequestHeaders_(HttpRequestHeaders(httpRequestStatusLine_)){

}
HttpRequestParser::HttpRequestParser(const HttpRequestParser& other)
    : httpRequestStatusLine_(other.httpRequestStatusLine_),
        httpGeneralHeaders_(HttpGeneralHeaders(httpRequestStatusLine_)),
        httpRequestHeaders_(HttpRequestHeaders(httpRequestStatusLine_)) {
    
}
HttpRequestParser::~HttpRequestParser(){

}

HttpRequestParser& HttpRequestParser::operator=(const HttpRequestParser& other){
    httpRequestStatusLine_ = other.httpRequestStatusLine_;
    httpGeneralHeaders_ = other.httpGeneralHeaders_;
    httpRequestHeaders_ = other.httpRequestHeaders_;
    return *this;
}

void HttpRequestParser::parseHttpRequest(const HttpRequestParser::BufferContainerType& buffer, int bufferSize, int lastSize){
    std::vector<std::string> content = parseBuffer_(buffer, bufferSize, lastSize);
    parseStatusLine_(content.at(0));
}
void HttpRequestParser::clear(){
    httpRequestStatusLine_ = HttpRequestStatusLine();
    httpGeneralHeaders_ = HttpGeneralHeaders(httpRequestStatusLine_);
    httpRequestHeaders_ = HttpRequestHeaders(httpRequestStatusLine_);
}

const HttpRequestStatusLine& HttpRequestParser::getStatusLine() const{
    return httpRequestStatusLine_;
}
const HttpGeneralHeaders& HttpRequestParser::getGeneralHeaders() const{
    return httpGeneralHeaders_;
}
const HttpRequestHeaders& HttpRequestParser::getRequestHeaders() const{
    return httpRequestHeaders_;
}

std::vector<std::string> HttpRequestParser::split_(const std::string& str, char delimiter){    
    std::string::const_iterator begin = str.begin(), end = str.begin();
    std::vector<std::string> result;
    while (true){
        end = std::find(begin, str.end(), delimiter);
        std::string substr(begin, end);
        if (substr.size()) result.push_back(substr);
        if (end == str.end()) break;
        begin = end + 1;
    }

    return result;
}
int HttpRequestParser::find_(char* arr, int startPoint, int size, char c){
    for (int i = startPoint; i < size; i++){
        if (arr[i] == c) return i;
    }
    return -1;
}

std::vector<std::string> HttpRequestParser::parseBuffer_(const BufferContainerType& buffer, int bufferSize, int lastSize){
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

    return result;
}
void HttpRequestParser::parseStatusLine_(const std::string& line){
    std::vector<std::string> splitedLine = split_(line, ' ');
    size_t splitedLineSize = splitedLine.size();
    if (splitedLineSize < 2 || splitedLineSize > 3) throw ExceptionType("Status line got invalid number of arguments", EXC_ARGS);
    
    // Method
    {
        const std::string& method = splitedLine.at(0);
        
        if (method == "GET") httpRequestStatusLine_.setMethod(HttpRequestStatusLine::GET);
        else if (method == "POST") httpRequestStatusLine_.setMethod(HttpRequestStatusLine::POST);
        else if (method == "DELETE") httpRequestStatusLine_.setMethod(HttpRequestStatusLine::DELETE);
        else throw ExceptionType("Invalid method", EXC_ARGS);
    }
    // URL
    {
        const std::string& url = splitedLine.at(1);
        httpRequestStatusLine_.setUrl(url);
    }
    // HTTP version
    {
        if (splitedLineSize == 2) {
            httpRequestStatusLine_.setHttpVersion(HttpRequestStatusLine::HTTP_0_9);
            return;
        }

        const std::string excMsg = "Invalid HTTP version";
        const std::string& verLine = splitedLine.at(2);

        if (verLine == "HTTP/0.9"){
            httpRequestStatusLine_.setHttpVersion(HttpRequestStatusLine::HTTP_0_9);
        } else if (verLine == "HTTP/1.0"){
            httpRequestStatusLine_.setHttpVersion(HttpRequestStatusLine::HTTP_1_0);
        } else if (verLine == "HTTP/1.1"){
            httpRequestStatusLine_.setHttpVersion(HttpRequestStatusLine::HTTP_1_1);
        } else if (verLine == "HTTP/1.1v2"){
            httpRequestStatusLine_.setHttpVersion(HttpRequestStatusLine::HTTP_1_1v2);
        } else if (verLine == "HTTP-Auth"){
            httpRequestStatusLine_.setHttpVersion(HttpRequestStatusLine::HTTP_AUTH);
        } else if (verLine == "MIME"){
            httpRequestStatusLine_.setHttpVersion(HttpRequestStatusLine::MIME);
        } else if (verLine == "MD5H"){
            httpRequestStatusLine_.setHttpVersion(HttpRequestStatusLine::MD5H);
        } else if (verLine == "CDH"){
            httpRequestStatusLine_.setHttpVersion(HttpRequestStatusLine::CDH);
        } else {
            throw ExceptionType("Invalid HTTP version", EXC_ARGS);
        }

        /*std::string::const_iterator slashIter = std::find(verLine.begin(), verLine.end(), '/');
        if (slashIter == verLine.end()) throw ExceptionType(excMsg, EXC_ARGS);

        const std::string protocolName = std::string(verLine.begin(), slashIter);
        if (protocolName != "HTTP") throw ExceptionType("Incorrect protocol", EXC_ARGS);

        const std::string httpVersionStr = std::string(slashIter + 1, verLine.end());
        {
            int dotsCount = 0;
            for (size_t i = 0; i < httpVersionStr.size(); i++){
                char curChar = httpVersionStr.at(i);
                
                if (curChar == '.') {
                    dotsCount++;
                    if (dotsCount > 1) throw ExceptionType(excMsg, EXC_ARGS);
                }
                else if (curChar < '0' || curChar > '9') throw ExceptionType(excMsg, EXC_ARGS);
            }

            std::stringstream stream(httpVersionStr);
            double httpVersionDouble;
            try {
                stream >> httpVersionDouble;
                httpRequestStatusLine_.setHttpVersion(httpVersionDouble);
            } catch (std::ios::failure& e) {
                throw ExceptionType(e.what(), EXC_ARGS);
            }

        }*/
    }
}
}
