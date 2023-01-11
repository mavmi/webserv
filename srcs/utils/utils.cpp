#include "../../include/utils/utils.hpp"

namespace MAIN_NAMESPACE::UTILS_NAMESPACE{
BytesContainer::BytesContainer()
    : bytesContainer(std::vector<char*>()),
        bufferSize(0),
        lastSize(0) {
    
}
BytesContainer::BytesContainer(const BytesContainer& other){
    cpy_(other);
}
BytesContainer::~BytesContainer(){
    free_();
}

BytesContainer& BytesContainer::operator=(const BytesContainer& other){
    free_();
    cpy_(other);
    return *this;
}

void BytesContainer::cpy_(const BytesContainer& other){
    for (size_t i = 0; i + 1 < other.bytesContainer.size(); i++){
        bytesContainer.push_back(realloc_(other.bytesContainer.at(i), other.bufferSize));
    }
    bytesContainer.push_back(realloc_(other.bytesContainer.back(), other.lastSize));
    bufferSize = other.bufferSize;
    lastSize = other.lastSize;
}
char* BytesContainer::realloc_(char* buffer, size_t bufferSize){
    char* newBuffer = new char[bufferSize];

    for (size_t i = 0; i < bufferSize; i++){
        newBuffer[i] = buffer[i];
    }

    return newBuffer;
}
void BytesContainer::free_(){
    for (size_t i = 0; i < bytesContainer.size(); i++){
        delete[] bytesContainer.at(i);
    }
}
}


namespace MAIN_NAMESPACE::UTILS_NAMESPACE{
UtilsException::UtilsException(const char* msg) 
    : msg_(std::string(msg)){}
UtilsException::UtilsException(const std::string& msg)
    : msg_(msg){}
UtilsException::~UtilsException() throw(){}
const std::string UtilsException::what() const throw(){
    return output_();
}
std::string UtilsException::output_() const {
    return "UTILS_EXCEPTION: " + msg_;
}
}


namespace MAIN_NAMESPACE::UTILS_NAMESPACE{
std::string     httpVersionToString(HTTP_VERSION httpVersion){
    if (httpVersion == MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_0_9){
        return "HTTP/0.9";
    } else if (httpVersion == MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0){
        return "HTTP/1.0";
    } else if (httpVersion == MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1){
        return "HTTP/1.1";
    } else if (httpVersion == MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1v2){
        return "HTTP/1.1v2";
    } else if (httpVersion == MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_AUTH){
        return "HTTP-Auth";
    } else if (httpVersion == MAIN_NAMESPACE::UTILS_NAMESPACE::MIME){
        return "MIME";
    } else if (httpVersion == MAIN_NAMESPACE::UTILS_NAMESPACE::MD5H){
        return "MD5H";
    } else if (httpVersion == MAIN_NAMESPACE::UTILS_NAMESPACE::CDH){
        return "CDH";
    } else {
        throw UtilsException("Invalid HTTP version");
    }
}
HTTP_VERSION    httpVersionFromString(const std::string& httpVersionStr){
    if (httpVersionStr == "HTTP/0.9"){
        return HTTP_0_9;
    } else if (httpVersionStr == "HTTP/1.0"){
        return HTTP_1_0;
    } else if (httpVersionStr == "HTTP/1.1"){
        return HTTP_1_1;
    } else if (httpVersionStr == "HTTP/1.1v2"){
        return HTTP_1_1v2;
    } else if (httpVersionStr == "HTTP-Auth"){
        return HTTP_AUTH;
    } else if (httpVersionStr == "MIME"){
        return MIME;
    } else if (httpVersionStr == "MD5H"){
        return MD5H;
    } else if (httpVersionStr == "CDH"){
        return CDH;
    } else {
        throw UtilsException("Invalid HTTP version");
    }
}

// Print message with specified message type
void utilsPrintMsg(const std::string& msg, MSG_TYPE msgType = INFO){
    std::string msgPrefix;
    
    switch (msgType){
        case DEBUG:
            msgPrefix = "DEBUG: ";
            break;
        case INFO:
            msgPrefix = "INFO: ";
            break;
        case WARNING:
            msgPrefix = "WARNING: ";
            break;
        case ERROR:
            msgPrefix = "ERROR: ";
            break;
        default:
            msgPrefix = "";
    }

    std::cout
        << msgPrefix
        << msg
        << std::endl;
}

// Check if number of arguments is valid.
// Exit on error
void utilsCheckArgsCount(int argc){
    if (argc > 2){
        utilsPrintMsg("configuration file required", ERROR);
        exit(1);
    }
}

}
