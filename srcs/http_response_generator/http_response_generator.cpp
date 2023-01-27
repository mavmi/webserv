#include "../../include/http_response_generator/http_response_generator.hpp"

namespace MAIN_NAMESPACE{
namespace HTTP_RESPONSE_GENER_NAMESPACE{
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
}


namespace MAIN_NAMESPACE{
namespace HTTP_RESPONSE_GENER_NAMESPACE{
HttpResponseGenerator::HttpResponseGenerator()
    : responseStatusLine_(MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseStatusLine()),
        generalHeaders_(MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeaders(responseStatusLine_)),
        responseHeaders_(MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeaders(responseStatusLine_)),
        message_(std::vector<std::string>()) {

}
HttpResponseGenerator::HttpResponseGenerator(const HttpResponseGenerator& other)
    : responseStatusLine_(other.responseStatusLine_),
        generalHeaders_(other.generalHeaders_),
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

MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeaders& HttpResponseGenerator::getGeneralHeaders(){
    return generalHeaders_;
}
const MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeaders& HttpResponseGenerator::getGeneralHeaders() const{
    return generalHeaders_;
}

MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeaders& HttpResponseGenerator::getResponseHeaders(){
    return responseHeaders_;
}
const MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeaders& HttpResponseGenerator::getResponseHeaders() const{
    return responseHeaders_;
}

std::vector<std::string>& HttpResponseGenerator::getMessage(){
    return message_;
}
const std::vector<std::string>& HttpResponseGenerator::getMessage() const{
    return message_;
}

MAIN_NAMESPACE::UTILS_NAMESPACE::BytesContainer HttpResponseGenerator::toBytes(){
    responseStatusLine_.done();
    responseHeaders_.done();
    
    const std::string newLine = "\n";
    MAIN_NAMESPACE::UTILS_NAMESPACE::BytesContainer result;

    // Status line
    {
        std::string statusLineStr;

        try{
            statusLineStr += MAIN_NAMESPACE::UTILS_NAMESPACE::httpVersionToString(responseStatusLine_.getHttpVersion());
        } catch (MAIN_NAMESPACE::UTILS_NAMESPACE::UtilsException& e){
            throw ExceptionType(e.what(), EXC_ARGS);
        }

        statusLineStr += " ";
        statusLineStr += responseStatusLine_.getStatusCode();

        try {
            statusLineStr += responseStatusLine_.getMessage();
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseStatusLineException&){}

        result.pushBack(statusLineStr);
        result.pushBack(newLine);
    }

    // Headers
    {
        // General headers
        try{
            result.pushBack("Cache-Control:" + generalHeaders_.getCacheControl());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeadersException&){}
        try{
            result.pushBack("Connection:" + generalHeaders_.getConnection());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeadersException&){}
        try{
            result.pushBack("Date:" + generalHeaders_.getDate());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeadersException&){}
        try{
            result.pushBack("MIME-Version:" + generalHeaders_.getMimeVersion());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeadersException&){}
        try{
            result.pushBack("Pragma:" + generalHeaders_.getPragma());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeadersException&){}
        try{
            result.pushBack("Trailer:" + generalHeaders_.getTrailer());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeadersException&){}
        try{
            result.pushBack("Transfer-Encoding:" + generalHeaders_.getTransferEncoding());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeadersException&){}
        try{
            result.pushBack("Upgrade:" + generalHeaders_.getUpgrade());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeadersException&){}
        try{
            result.pushBack("Via:" + generalHeaders_.getVia());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeadersException&){}
        try{
            result.pushBack("Warning:" + generalHeaders_.getWarning());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeadersException&){}

        // Common headers
        try{
            result.pushBack("Content-Disposition:" + responseHeaders_.getContentDisposition());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Content-Encoding:" + responseHeaders_.getContentEncoding());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Content-Language:" + responseHeaders_.getContentLanguage());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Content-Length:" + responseHeaders_.getContentLength());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Content-Location:" + responseHeaders_.getContentLocation());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Content-MD5:" + responseHeaders_.getContentMD5());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Content-Range:" + responseHeaders_.getContentRange());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Content-Type:" + responseHeaders_.getContentType());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Content-Version:" + responseHeaders_.getContentVersion());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Derived-From:" + responseHeaders_.getDerivedFrom());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Expires:" + responseHeaders_.getExpires());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Last-Modified:" + responseHeaders_.getLastModified());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Link:" + responseHeaders_.getLink());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Title:" + responseHeaders_.getTitle());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}

        // Response headers
        try{
            result.pushBack("Accept-Ranges:" + responseHeaders_.getAcceptRanges());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
        try{
            result.pushBack("Age:" + responseHeaders_.getAge());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
        try{
            result.pushBack("Allow:" + responseHeaders_.getAllow());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
        try{
            result.pushBack("Alternates:" + responseHeaders_.getAlternates());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
        try{
            result.pushBack("ETag:" + responseHeaders_.getETag());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
        try{
            result.pushBack("Location:" + responseHeaders_.getLocation());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
        try{
            result.pushBack("Proxy-Authenticate:" + responseHeaders_.getProxyAuthenticate());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
        try{
            result.pushBack("Public:"  + responseHeaders_.getPublic());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
        try{
            result.pushBack("Retry-After:" + responseHeaders_.getRetryAfter());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
        try{
            result.pushBack("Server:" + responseHeaders_.getServer());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
        try{
            result.pushBack("Vary:" + responseHeaders_.getVary());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
        try{
            result.pushBack("WWW-Authenticate:" + responseHeaders_.getWWWAuthenticate());
            result.pushBack(newLine);
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
    }

    // Message
    {
        result.pushBack(newLine);
        for (size_t i = 0; i < message_.size(); i++){
            result.pushBack(message_[i]);
            if (i + 1 != message_.size()) result.pushBack(newLine);
        }
    }

    return result;
}
}
}
