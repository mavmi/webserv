#include "../../include/http_request_parser/http_request_parser.hpp"

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
        httpRequestHeaders_(HttpRequestHeaders(httpRequestStatusLine_)),
        httpRequestContent_(std::vector<std::string>()){

}
HttpRequestParser::HttpRequestParser(const HttpRequestParser& other)
    : httpRequestStatusLine_(other.httpRequestStatusLine_),
        httpGeneralHeaders_(HttpGeneralHeaders(httpRequestStatusLine_)),
        httpRequestHeaders_(HttpRequestHeaders(httpRequestStatusLine_)),
        httpRequestContent_(std::vector<std::string>()) {
    
}
HttpRequestParser::~HttpRequestParser(){

}

HttpRequestParser& HttpRequestParser::operator=(const HttpRequestParser& other){
    httpRequestStatusLine_ = other.httpRequestStatusLine_;
    httpGeneralHeaders_ = other.httpGeneralHeaders_;
    httpRequestHeaders_ = other.httpRequestHeaders_;
    httpRequestContent_ = other.httpRequestContent_;
    return *this;
}

void HttpRequestParser::parseHttpRequest(const HttpRequestParser::BufferContainerType& buffer, int bufferSize, int lastSize){
    std::vector<std::string> content = parseBuffer_(buffer, bufferSize, lastSize);
    if (content.size() < 2) throw ExceptionType("HTTP request doesn't contain headers");

    parseStatusLine_(content.at(0));

    size_t i = 1;
    while (i < content.size() && !isLineEmpty_(content[i])){
        parseHeader_(content[i++]);
    }
    httpGeneralHeaders_.done();
    httpRequestHeaders_.done();

    i++;
    while (i < content.size()){
        httpRequestContent_.push_back(content[i++]);
    }
}
void HttpRequestParser::clear(){
    httpRequestStatusLine_ = HttpRequestStatusLine();
    httpGeneralHeaders_ = HttpGeneralHeaders(httpRequestStatusLine_);
    httpRequestHeaders_ = HttpRequestHeaders(httpRequestStatusLine_);
    httpRequestContent_ = std::vector<std::string>();
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
const std::vector<std::string>& HttpRequestParser::getRequestContent() const{
    return httpRequestContent_;
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
bool HttpRequestParser::isLineEmpty_(const std::string& line){
    for (size_t i = 0; i < line.size(); i++){
        if (!std::isspace(line[i])) return false;
    }
    return true;
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
                i + 1 == buffer.size() ? lastSize : bufferSize,
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
        
        if (method == "GET") httpRequestStatusLine_.setMethod(MAIN_NAMESPACE::UTILS_NAMESPACE::GET);
        else if (method == "POST") httpRequestStatusLine_.setMethod(MAIN_NAMESPACE::UTILS_NAMESPACE::POST);
        else if (method == "DELETE") httpRequestStatusLine_.setMethod(MAIN_NAMESPACE::UTILS_NAMESPACE::DELETE);
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
            httpRequestStatusLine_.setHttpVersion(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_0_9);
            return;
        }

        const std::string excMsg = "Invalid HTTP version";
        const std::string& verLine = splitedLine.at(2);

        if (verLine == "HTTP/0.9"){
            httpRequestStatusLine_.setHttpVersion(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_0_9);
        } else if (verLine == "HTTP/1.0"){
            httpRequestStatusLine_.setHttpVersion(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
        } else if (verLine == "HTTP/1.1"){
            httpRequestStatusLine_.setHttpVersion(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
        } else if (verLine == "HTTP/1.1v2"){
            httpRequestStatusLine_.setHttpVersion(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1v2);
        } else if (verLine == "HTTP-Auth"){
            httpRequestStatusLine_.setHttpVersion(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_AUTH);
        } else if (verLine == "MIME"){
            httpRequestStatusLine_.setHttpVersion(MAIN_NAMESPACE::UTILS_NAMESPACE::MIME);
        } else if (verLine == "MD5H"){
            httpRequestStatusLine_.setHttpVersion(MAIN_NAMESPACE::UTILS_NAMESPACE::MD5H);
        } else if (verLine == "CDH"){
            httpRequestStatusLine_.setHttpVersion(MAIN_NAMESPACE::UTILS_NAMESPACE::CDH);
        } else {
            throw ExceptionType("Invalid HTTP version", EXC_ARGS);
        }
    }

    httpRequestStatusLine_.done();
}
void HttpRequestParser::parseHeader_(const std::string& line){
    const std::vector<std::string> splittedLine = split_(line, ':');
    if (splittedLine.size() != 2) throw ExceptionType("Invalid header line");

    const std::string& key = splittedLine.at(0);
    const std::string& value = splittedLine.at(1);

    // General headers
    if (key == "Cache-Control"){
        httpGeneralHeaders_.setCacheControl(value);
    } else if (key == "Connection"){
        httpGeneralHeaders_.setConnection(value);
    } else if (key == "Date"){
        httpGeneralHeaders_.setDate(value);
    } else if (key == "MIME-Version"){
        httpGeneralHeaders_.setMimeVersion(value);
    } else if (key == "Pragma"){
        httpGeneralHeaders_.setPragma(value);
    } else if (key == "Trailer"){
        httpGeneralHeaders_.setTrailer(value);
    } else if (key == "Transfer-Encoding"){
        httpGeneralHeaders_.setTransferEncoding(value);
    } else if (key ==  "Upgrade"){
        httpGeneralHeaders_.setUpgrade(value);
    } else if (key == "Via"){
        httpGeneralHeaders_.setVia(value);
    } else if (key == "Warning"){
        httpGeneralHeaders_.setWarning(value);
    }
    // Request headers
    else if (key == "Accept"){
        httpRequestHeaders_.setAccept(value);   
    } else if (key == "Accept-Charset"){
        httpRequestHeaders_.setAcceptCharset(value);
    } else if (key == "Accept-Encoding"){
        httpRequestHeaders_.setAcceptEncoding(value);
    } else if (key == "Accept-Language"){
        httpRequestHeaders_.setAcceptLanguage(value);
    } else if (key == "Authorization"){
        httpRequestHeaders_.setAuthorization(value);
    } else if (key == "Content-Disposition"){
        httpRequestHeaders_.setContentDisposition(value);
    } else if (key == "Content-Encoding"){
        httpRequestHeaders_.setContentEncoding(value);
    } else if (key == "Content-Language"){
        httpRequestHeaders_.setContentLanguage(value);
    } else if (key == "Content-Length"){
        httpRequestHeaders_.setContentLength(value);
    } else if (key == "Content-Location"){
        httpRequestHeaders_.setContentLocation(value);
    } else if (key == "Content-MD5"){
        httpRequestHeaders_.setContentMD5(value);
    } else if (key == "Content-Range"){
        httpRequestHeaders_.setContentRange(value);
    } else if (key == "Content-Type"){
        httpRequestHeaders_.setContentType(value);
    } else if (key == "Content-Version"){
        httpRequestHeaders_.setContentVersion(value);
    } else if (key == "Derived-From"){
        httpRequestHeaders_.setDerivedFrom(value);
    } else if (key == "Expect"){
        httpRequestHeaders_.setExpect(value);
    } else if (key == "Expires"){
        httpRequestHeaders_.setExpires(value);
    } else if (key == "From"){
        httpRequestHeaders_.setFrom(value);
    } else if (key == "Host"){
        httpRequestHeaders_.setHost(value);
    } else if (key == "If-Match"){
        httpRequestHeaders_.setIfMatch(value);
    } else if (key == "If-Modified-Since"){
        httpRequestHeaders_.setIfModifiedSince(value);
    } else if (key == "If-None-Match"){
        httpRequestHeaders_.setIfNoneMatch(value);
    } else if (key == "If-Range"){
        httpRequestHeaders_.setIfRange(value);
    } else if (key == "If-Unmodified-Since"){
        httpRequestHeaders_.setIfUnmodifiedSince(value);
    } else if (key == "Last-Modified"){
        httpRequestHeaders_.setLastModified(value);
    } else if (key == "Link"){
        httpRequestHeaders_.setLink(value);
    } else if (key == "Max-Forwards"){
        httpRequestHeaders_.setMaxForwards(value);
    } else if (key == "Proxy-Authorization"){
        httpRequestHeaders_.setProxyAuthorization(value);
    } else if (key == "Range"){
        httpRequestHeaders_.setRange(value);
    } else if (key == "Referer"){
        httpRequestHeaders_.setReferer(value);
    } else if (key == "Title"){
        httpRequestHeaders_.setTitle(value);
    } else if (key == "TE"){
        httpRequestHeaders_.setTE(value);
    } else if (key == "User-Agent"){
        httpRequestHeaders_.setUserAgent(value);
    }
}
}
