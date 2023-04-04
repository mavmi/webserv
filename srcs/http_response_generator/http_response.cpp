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
            statusLineStr += " ";
            statusLineStr += responseStatusLine_.getMessage();
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseStatusLineException&){}

        result.pushBack(statusLineStr);
    }

    // Headers
    {
        // General headers
        try{
            result.pushBack("Cache-Control: " + generalHeaders_.getCacheControl());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeadersException&){}
        try{
            result.pushBack("Connection: " + generalHeaders_.getConnection());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeadersException&){}
        try{
            result.pushBack("Date: " + generalHeaders_.getDate());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeadersException&){}
        try{
            result.pushBack("MIME-Version: " + generalHeaders_.getMimeVersion());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeadersException&){}
        try{
            result.pushBack("Pragma: " + generalHeaders_.getPragma());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeadersException&){}
        try{
            result.pushBack("Trailer: " + generalHeaders_.getTrailer());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeadersException&){}
        try{
            result.pushBack("Transfer-Encoding: " + generalHeaders_.getTransferEncoding());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeadersException&){}
        try{
            result.pushBack("Upgrade: " + generalHeaders_.getUpgrade());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeadersException&){}
        try{
            result.pushBack("Via: " + generalHeaders_.getVia());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeadersException&){}
        try{
            result.pushBack("Warning: " + generalHeaders_.getWarning());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpGeneralHeadersException&){}

        // Common headers
        try{
            result.pushBack("Content-Disposition: " + responseHeaders_.getContentDisposition());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Content-Encoding: " + responseHeaders_.getContentEncoding());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Content-Language: " + responseHeaders_.getContentLanguage());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Content-Length: " + responseHeaders_.getContentLength());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Content-Location: " + responseHeaders_.getContentLocation());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Content-MD5: " + responseHeaders_.getContentMD5());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Content-Range: " + responseHeaders_.getContentRange());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Content-Type: " + responseHeaders_.getContentType());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Content-Version: " + responseHeaders_.getContentVersion());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Derived-From: " + responseHeaders_.getDerivedFrom());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Expires: " + responseHeaders_.getExpires());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Last-Modified: " + responseHeaders_.getLastModified());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Link: " + responseHeaders_.getLink());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}
        try{
            result.pushBack("Title: " + responseHeaders_.getTitle());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpCommonHeadersException&){}

        // Response headers
        try{
            result.pushBack("Accept-Ranges: " + responseHeaders_.getAcceptRanges());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
        try{
            result.pushBack("Age: " + responseHeaders_.getAge());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
        try{
            result.pushBack("Allow: " + responseHeaders_.getAllow());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
        try{
            result.pushBack("Alternates: " + responseHeaders_.getAlternates());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
        try{
            result.pushBack("ETag: " + responseHeaders_.getETag());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
        try{
            result.pushBack("Location: " + responseHeaders_.getLocation());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
        try{
            result.pushBack("Proxy-Authenticate: " + responseHeaders_.getProxyAuthenticate());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
        try{
            result.pushBack("Public: "  + responseHeaders_.getPublic());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
        try{
            result.pushBack("Retry-After: " + responseHeaders_.getRetryAfter());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
        try{
            result.pushBack("Server: " + responseHeaders_.getServer());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
        try{
            result.pushBack("Vary: " + responseHeaders_.getVary());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
        try{
            result.pushBack("WWW-Authenticate: " + responseHeaders_.getWWWAuthenticate());
        } catch (MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE::HttpResponseHeadersException&){}
    }

    // Message
    {
        result.pushBack("");
        result.pushBack(std::string(message_.begin(), message_.end()));
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
            MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_VERSION httpVersion,
            std::string statusCode,
            std::string message
        ){
    responseStatusLine_.setHttpVersion(httpVersion);
    responseStatusLine_.setStatusCode(statusCode);
    responseStatusLine_.setMessage(message);
}
bool HttpResponse::setupFile(const std::string& filePath, const std::string& errFilePath){
    struct stat buf;
    std::fstream inputStream;
    const std::string* workingFile = NULL;


    // Get info about file
    inputStream.open(filePath.c_str(), std::ios::in | std::ios::binary);
    if (!inputStream.is_open() || stat(filePath.c_str(), &buf) != 0){
        inputStream.open(errFilePath.c_str(), std::ios::in | std::ios::binary);
        if (!inputStream.is_open() || stat(errFilePath.c_str(), &buf) != 0){
            inputStream.close();
            return setupFileOnError();
        } else {
            workingFile = &errFilePath;
        }
    } else {
        workingFile = &filePath;
    }

    try {
        // Last modified
        #ifdef __APPLE__
        responseHeaders_.setLastModified(std::localtime(&buf.st_mtimespec.tv_sec));
        #else
        responseHeaders_.setLastModified(std::localtime(&buf.st_mtim.tv_sec));
        #endif
        // Content length
        responseHeaders_.setContentLength(MAIN_NAMESPACE::UTILS_NAMESPACE::utilsNumToString(buf.st_size));
    } catch (MAIN_NAMESPACE::UTILS_NAMESPACE::Exception& e){
        return setupFileOnError();
    }
    // Save file's data
    {
        std::string line;
        while (std::getline(inputStream, line)){
            if (message_.size()) message_.push_back('\n');
            for (size_t i = 0; i < line.size(); i++){
                message_.push_back(line[i]);
            }
        }
    }

    try {
        // Content type
        responseHeaders_.setContentType(parseFileSignature_(*workingFile));
    } catch (MAIN_NAMESPACE::UTILS_NAMESPACE::Exception& e){
        std::cout << e.what() << std::endl;
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
    if (ext == "js"){
        return "text/javascript";
    } else if (ext == "html") {
        return "text/html";
    } else if (ext == "php") {
        return "text/php";
    }

    throw ExceptionType("Unknown file extension");
}
}
