#include "../../includes/http_request_parser/http_request_parser.hpp"
// #include "http_request_parser.hpp"

namespace MAIN_NAMESPACE{
namespace HTTP_REQUEST_PARS_NAMESPACE{
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
}


namespace MAIN_NAMESPACE{
namespace HTTP_REQUEST_PARS_NAMESPACE{
HttpRequestParser::HttpRequestParser(){

}
HttpRequestParser::HttpRequestParser(const HttpRequestParser& other)
    : httpRequest_(other.httpRequest_) {
    
}
HttpRequestParser::~HttpRequestParser(){

}

HttpRequestParser& HttpRequestParser::operator=(const HttpRequestParser& other){
    httpRequest_ = other.httpRequest_;
    return *this;
}

const HttpRequest& HttpRequestParser::parseHttpRequest(const MAIN_NAMESPACE::UTILS_NAMESPACE::BytesContainer& buffer){
    // std::vector<std::string> content = parseBuffer_(buffer);
    const std::vector<std::string>& content = buffer.getData();
    if (content.size() < 2) throw ExceptionType("HTTP request doesn't contain headers");

    parseStatusLine_(content.at(0));

    size_t i = 1;
    while (i < content.size() && !isLineEmpty_(content[i])){
        parseHeader_(content[i++]);
    }
    httpRequest_.getGeneralHeaders().done();
    httpRequest_.getRequestHeaders().done();

    i++;
    while (i < content.size()){
        httpRequest_.getRequestContent().push_back(content[i++]);
    }

    return httpRequest_;
}
const HttpRequest& HttpRequestParser::getHttpRequest() const{
    return httpRequest_;
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

/*std::vector<std::string> HttpRequestParser::parseBuffer_(const MAIN_NAMESPACE::UTILS_NAMESPACE::BytesContainer& buffer){
    int startPoint;
    bool isLastFinished = true;
    const char newLine = '\n';
    std::vector<std::string> result;

    for (size_t i = 0; i < buffer.bytesContainer.size(); i++){
        startPoint = 0;
        while (true){
            int newLinePos = find_(
                buffer.bytesContainer[i],
                startPoint,
                i + 1 == buffer.bytesContainer.size() ? buffer.lastSize : buffer.bufferSize,
                newLine
            );
            
            int endPoint = newLinePos == -1 ? (i + 1 == buffer.bytesContainer.size() ? buffer.lastSize : buffer.bufferSize) : newLinePos;
            std::string substr(
                buffer.bytesContainer[i] + startPoint,
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
}*/

/*std::vector<std::string> HttpRequestParser::parseBuffer_(const MAIN_NAMESPACE::UTILS_NAMESPACE::BytesContainer &buffer)
{
    return std::vector<std::string>();
}*/
void HttpRequestParser::parseStatusLine_(const std::string &line)
{
    std::vector<std::string> splitedLine = split_(line, ' ');
    size_t splitedLineSize = splitedLine.size();
    if (splitedLineSize < 2 || splitedLineSize > 3) throw ExceptionType("Status line got invalid number of arguments", EXC_ARGS);
    
    // Method
    {
        const std::string& method = splitedLine.at(0);
        
        if (method == "GET") httpRequest_.getStatusLine().setMethod(MAIN_NAMESPACE::UTILS_NAMESPACE::GET);
        else if (method == "POST") httpRequest_.getStatusLine().setMethod(MAIN_NAMESPACE::UTILS_NAMESPACE::POST);
        else if (method == "DELETE") httpRequest_.getStatusLine().setMethod(MAIN_NAMESPACE::UTILS_NAMESPACE::DELETE);
        else throw ExceptionType("Invalid method", EXC_ARGS);
    }
    // URL
    {
        const std::string& url = splitedLine.at(1);
        httpRequest_.getStatusLine().setUrl(url);
    }
    // HTTP version
    {
        if (splitedLineSize == 2) {
            httpRequest_.getStatusLine().setHttpVersion(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_0_9);
            return;
        }

        const std::string excMsg = "Invalid HTTP version";
        const std::string& verLine = splitedLine.at(2);

        try {
            httpRequest_.getStatusLine().setHttpVersion(MAIN_NAMESPACE::UTILS_NAMESPACE::httpVersionFromString(verLine));
        } catch (MAIN_NAMESPACE::UTILS_NAMESPACE::UtilsException& e){
            throw ExceptionType(e.what(), EXC_ARGS);
        }
    }

    httpRequest_.getStatusLine().done();
}
void HttpRequestParser::parseHeader_(const std::string& line){
    const std::vector<std::string> splittedLine = split_(line, ':');
    if (splittedLine.size() != 2) throw ExceptionType("Invalid header line");

    const std::string& key = splittedLine.at(0);
    const std::string& value = splittedLine.at(1);

    // General headers
    if (key == "Cache-Control"){
        httpRequest_.getGeneralHeaders().setCacheControl(value);
    } else if (key == "Connection"){
        httpRequest_.getGeneralHeaders().setConnection(value);
    } else if (key == "Date"){
        httpRequest_.getGeneralHeaders().setDate(value);
    } else if (key == "MIME-Version"){
        httpRequest_.getGeneralHeaders().setMimeVersion(value);
    } else if (key == "Pragma"){
        httpRequest_.getGeneralHeaders().setPragma(value);
    } else if (key == "Trailer"){
        httpRequest_.getGeneralHeaders().setTrailer(value);
    } else if (key == "Transfer-Encoding"){
        httpRequest_.getGeneralHeaders().setTransferEncoding(value);
    } else if (key ==  "Upgrade"){
        httpRequest_.getGeneralHeaders().setUpgrade(value);
    } else if (key == "Via"){
        httpRequest_.getGeneralHeaders().setVia(value);
    } else if (key == "Warning"){
        httpRequest_.getGeneralHeaders().setWarning(value);
    }
    // Request headers
    else if (key == "Accept"){
        httpRequest_.getRequestHeaders().setAccept(value);   
    } else if (key == "Accept-Charset"){
        httpRequest_.getRequestHeaders().setAcceptCharset(value);
    } else if (key == "Accept-Encoding"){
        httpRequest_.getRequestHeaders().setAcceptEncoding(value);
    } else if (key == "Accept-Language"){
        httpRequest_.getRequestHeaders().setAcceptLanguage(value);
    } else if (key == "Authorization"){
        httpRequest_.getRequestHeaders().setAuthorization(value);
    } else if (key == "Content-Disposition"){
        httpRequest_.getRequestHeaders().setContentDisposition(value);
    } else if (key == "Content-Encoding"){
        httpRequest_.getRequestHeaders().setContentEncoding(value);
    } else if (key == "Content-Language"){
        httpRequest_.getRequestHeaders().setContentLanguage(value);
    } else if (key == "Content-Length"){
        httpRequest_.getRequestHeaders().setContentLength(value);
    } else if (key == "Content-Location"){
        httpRequest_.getRequestHeaders().setContentLocation(value);
    } else if (key == "Content-MD5"){
        httpRequest_.getRequestHeaders().setContentMD5(value);
    } else if (key == "Content-Range"){
        httpRequest_.getRequestHeaders().setContentRange(value);
    } else if (key == "Content-Type"){
        httpRequest_.getRequestHeaders().setContentType(value);
    } else if (key == "Content-Version"){
        httpRequest_.getRequestHeaders().setContentVersion(value);
    } else if (key == "Derived-From"){
        httpRequest_.getRequestHeaders().setDerivedFrom(value);
    } else if (key == "Expect"){
        httpRequest_.getRequestHeaders().setExpect(value);
    } else if (key == "Expires"){
        httpRequest_.getRequestHeaders().setExpires(value);
    } else if (key == "From"){
        httpRequest_.getRequestHeaders().setFrom(value);
    } else if (key == "Host"){
        httpRequest_.getRequestHeaders().setHost(value);
    } else if (key == "If-Match"){
        httpRequest_.getRequestHeaders().setIfMatch(value);
    } else if (key == "If-Modified-Since"){
        httpRequest_.getRequestHeaders().setIfModifiedSince(value);
    } else if (key == "If-None-Match"){
        httpRequest_.getRequestHeaders().setIfNoneMatch(value);
    } else if (key == "If-Range"){
        httpRequest_.getRequestHeaders().setIfRange(value);
    } else if (key == "If-Unmodified-Since"){
        httpRequest_.getRequestHeaders().setIfUnmodifiedSince(value);
    } else if (key == "Last-Modified"){
        httpRequest_.getRequestHeaders().setLastModified(value);
    } else if (key == "Link"){
        httpRequest_.getRequestHeaders().setLink(value);
    } else if (key == "Max-Forwards"){
        httpRequest_.getRequestHeaders().setMaxForwards(value);
    } else if (key == "Proxy-Authorization"){
        httpRequest_.getRequestHeaders().setProxyAuthorization(value);
    } else if (key == "Range"){
        httpRequest_.getRequestHeaders().setRange(value);
    } else if (key == "Referer"){
        httpRequest_.getRequestHeaders().setReferer(value);
    } else if (key == "Title"){
        httpRequest_.getRequestHeaders().setTitle(value);
    } else if (key == "TE"){
        httpRequest_.getRequestHeaders().setTE(value);
    } else if (key == "User-Agent"){
        httpRequest_.getRequestHeaders().setUserAgent(value);
    }
}
}
}