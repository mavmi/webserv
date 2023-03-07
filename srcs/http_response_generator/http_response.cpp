#include "../../includes/http_response_generator/http_response.hpp"

namespace MAIN_NAMESPACE{
HttpResponseException::HttpResponseException(const char* msg) : Exception(msg){}
HttpResponseException::HttpResponseException(const std::string& msg) : Exception(msg){}
HttpResponseException::HttpResponseException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpResponseException::HttpResponseException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpResponseException::HttpResponseException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
HttpResponseException::HttpResponseException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string HttpResponseException::output_() const {
    return "HTTP_RESPONSE_EXCEPTION: " + msg_;
}
}


namespace MAIN_NAMESPACE{
HttpResponse::HttpResponse()
    : responseStatusLine_(MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseStatusLine()),
        generalHeaders_(MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeaders(responseStatusLine_)),
        responseHeaders_(MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeaders(responseStatusLine_)),
        message_(std::vector<char>()) {

}
HttpResponse::HttpResponse(const HttpResponse& other)
    : responseStatusLine_(other.responseStatusLine_),
        generalHeaders_(other.generalHeaders_),
        responseHeaders_(other.responseHeaders_),
        message_(other.message_){

}
HttpResponse::~HttpResponse(){

}

HttpResponse& HttpResponse::operator=(const HttpResponse& other){
    responseStatusLine_ = other.responseStatusLine_;
    responseHeaders_ = other.responseHeaders_;
    message_ = other.message_;
    return *this;
}

MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseStatusLine& HttpResponse::getStatusLine(){
    return responseStatusLine_;
}
const MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseStatusLine& HttpResponse::getStatusLine() const{
    return responseStatusLine_;
}

MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeaders& HttpResponse::getGeneralHeaders(){
    return generalHeaders_;
}
const MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeaders& HttpResponse::getGeneralHeaders() const{
    return generalHeaders_;
}

MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeaders& HttpResponse::getResponseHeaders(){
    return responseHeaders_;
}
const MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeaders& HttpResponse::getResponseHeaders() const{
    return responseHeaders_;
}

std::vector<char>& HttpResponse::getMessage(){
    return message_;
}
const std::vector<char>& HttpResponse::getMessage() const{
    return message_;
}

MAIN_NAMESPACE::UTILS_NAMESPACE::BytesContainer HttpResponse::toBytes(){
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

void HttpResponse::setDate(){
    generalHeaders_.setDate();
}
void HttpResponse::setRetryAfter(){
    responseHeaders_.setRetryAfter();
}
void HttpResponse::setStatusLine(
            MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::StatusLineAbstractParent::HttpVersionType httpVersion,
            MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseStatusLine::StatusCodeType statusCode,
            MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::
            HttpResponseStatusLine::MessageType message
        ){
    responseStatusLine_.setHttpVersion(httpVersion);
    responseStatusLine_.setStatusCode(statusCode);
    responseStatusLine_.setMessage(message);
}
bool HttpResponse::setupFile(const std::string& filePath){
    struct stat buf;
    std::fstream inputFile;

    // Get info about file
    inputFile.open(filePath, std::ios::in | std::ios::binary);
    if (!inputFile.is_open() || stat(filePath.c_str(), &buf) != 0){
        inputFile.close();
        return setupFileOnError();
    }

    try {
        // Last modified
        responseHeaders_.setLastModified(std::localtime(&buf.st_mtimespec.tv_sec));
        // Content length
        responseHeaders_.setContentLength(MAIN_NAMESPACE::UTILS_NAMESPACE::utilsNumToString(buf.st_size));
    } catch (MAIN_NAMESPACE::UTILS_NAMESPACE::Exception&){
        return setupFileOnError();
    }
    // Save file's data
    {
        const size_t bufferSize = 256;
        char *buffer = new char[bufferSize];

        message_.clear();
        while (inputFile.read(buffer, bufferSize)){
            for (int i = 0; i < inputFile.gcount(); i++){
                message_.push_back(buffer[i]);
            }
        }

        delete[] buffer;
    }

    try {
        // Content type
        responseHeaders_.setContentType(parseFileSignature_(filePath));
    } catch (MAIN_NAMESPACE::UTILS_NAMESPACE::Exception&){
        return setupFileOnError();
    }

    return true;
}

bool HttpResponse::setupFileOnError(){
    static const std::string errorContent = "<html><body><h1>Error</h1></body></html>";

    try{
        std::time_t t = std::time(NULL);
        std::tm* timeNow = std::localtime(&t);

        responseHeaders_.setLastModified(timeNow);
        responseHeaders_.setContentLength(MAIN_NAMESPACE::UTILS_NAMESPACE::utilsNumToString<size_t>(errorContent.size()));

        message_.clear();
        for (size_t i = 0; i < errorContent.size(); i++) message_.push_back(errorContent[i]);
        responseHeaders_.setContentType("text/html");
    } catch (MAIN_NAMESPACE::UTILS_NAMESPACE::Exception&){}

    return false;
}
std::string HttpResponse::parseFileSignature_(const std::string& fileName) const{
    static bool init = false;
    static std::vector<std::string> extensions;
    static std::vector< std::vector<char> > signatures;

    if (!init){
        init = true;

        {
            extensions.push_back("image/jpeg");
            signatures.push_back(std::vector<char>());
            signatures.back().push_back(0xFF);
            signatures.back().push_back(0xD8);
            signatures.back().push_back(0xFF);
            signatures.back().push_back(0xE0);
            signatures.back().push_back(0x00);
            signatures.back().push_back(0x10);
            signatures.back().push_back(0x4A);
            signatures.back().push_back(0x46);
            signatures.back().push_back(0x49);
            signatures.back().push_back(0x46);
            signatures.back().push_back(0x00);
            signatures.back().push_back(0x01);
        }
        {
            extensions.push_back("image/jpeg");
            signatures.push_back(std::vector<char>());
            signatures.back().push_back(0xFF);
            signatures.back().push_back(0xD8);
            signatures.back().push_back(0xFF);
            signatures.back().push_back(0xEE);
        }
        {
            extensions.push_back("image/jpeg");
            signatures.push_back(std::vector<char>());
            signatures.back().push_back(0xFF);
            signatures.back().push_back(0xD8);
            signatures.back().push_back(0xFF);
            signatures.back().push_back(0xE0);
        }
        {
            extensions.push_back("image/png");
            signatures.push_back(std::vector<char>());
            signatures.back().push_back(0x89);
            signatures.back().push_back(0x50);
            signatures.back().push_back(0x4E);
            signatures.back().push_back(0x47);
            signatures.back().push_back(0x0D);
            signatures.back().push_back(0x0A);
            signatures.back().push_back(0x1A);
            signatures.back().push_back(0x0A);
        }
        {
            extensions.push_back("video/mp4");
            signatures.push_back(std::vector<char>());
            signatures.back().push_back(0x66);
            signatures.back().push_back(0x74);
            signatures.back().push_back(0x79);
            signatures.back().push_back(0x70);
            signatures.back().push_back(0x69);
            signatures.back().push_back(0x73);
            signatures.back().push_back(0x6F);
            signatures.back().push_back(0x6D);
        }
        {
            extensions.push_back("audio/mpeg");
            signatures.push_back(std::vector<char>());
            signatures.back().push_back(0x49);
            signatures.back().push_back(0x44);
            signatures.back().push_back(0x33);
        }
        {
            extensions.push_back("text/html");
            signatures.push_back(std::vector<char>());
            signatures.back().push_back(0x3C);
            signatures.back().push_back(0x68);
            signatures.back().push_back(0x74);
            signatures.back().push_back(0x6D);
            signatures.back().push_back(0x6C);
        }
    }

    for (size_t sig_i = 0; sig_i < signatures.size(); sig_i++){
        const std::vector<char>& signature = signatures.at(sig_i);

        if (message_.size() < signature.size()) continue;
        for (size_t j = 0, i = 0; i < signature.size(); i++, j++){
            if (message_[j] != signature[i]) break;
            else if (i + 1 == signature.size()) return extensions.at(sig_i);
        }
    };

    return parseFileExtension_(fileName);
}
std::string HttpResponse::parseFileExtension_(const std::string& fileName) const{
    size_t dotPos = fileName.rfind('.');
    if (dotPos == std::string::npos) return "";

    const std::string ext = fileName.substr(dotPos + 1, fileName.size() - dotPos - 1);
    if (ext == ".js"){
        return "text/javascript";
    }

    throw ExceptionType("Unknown file extension");
}
}
