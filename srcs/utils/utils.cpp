#include "../../includes/utils/utils.hpp"

namespace MAIN_NAMESPACE{
namespace UTILS_NAMESPACE{
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
}


namespace MAIN_NAMESPACE{
namespace UTILS_NAMESPACE{
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
const char* utilsStringToCharArray(const std::string& str){
    char* arr = new char[str.size() + 1];
    
    size_t i;
    for (i = 0; i < str.size(); i++){
        arr[i] = str[i];
    }
    arr[i] = '\0';

    return arr;
}
}
}


namespace MAIN_NAMESPACE{
namespace UTILS_NAMESPACE{
BytesContainer::BytesContainer()
    : bytesContainer(std::vector<char*>()),
        bufferSize(BUFFER_SIZE),
        lastSize(0) {
    
}
BytesContainer::BytesContainer(const BytesContainer& other)
    : bufferSize(BUFFER_SIZE) {
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

void BytesContainer::pushBack(const std::string& line){
    if (lastSize == bufferSize || bytesContainer.empty()){
        lastSize = 0;
        bytesContainer.push_back(new char[bufferSize]);
    }

    size_t i = 0;
    while (true){
        while (i < line.size() && lastSize < bufferSize){
            bytesContainer.back()[lastSize++] = line.at(i++);
        }

        if (i == line.size()) {
            break;
        }

        lastSize = 0;
        bytesContainer.push_back(new char[bufferSize]);
    }
}

void BytesContainer::cpy_(const BytesContainer& other){
    if (other.bytesContainer.size()){
        for (size_t i = 0; i + 1 < other.bytesContainer.size(); i++){
            bytesContainer.push_back(realloc_(other.bytesContainer.at(i), other.bufferSize));
        }
        bytesContainer.push_back(realloc_(other.bytesContainer.back(), other.lastSize));
    }
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
}


namespace MAIN_NAMESPACE{
namespace UTILS_NAMESPACE{
ArrayContainer::ArrayContainer()
    : data_(NULL), size_(0) {
    
}
ArrayContainer::ArrayContainer(const ArrayContainer& other)
    : data_(NULL), size_(0) {
    cpy_(other);
}
ArrayContainer::~ArrayContainer(){
    free_();
}

ArrayContainer& ArrayContainer::operator=(const ArrayContainer& other){
    free_();
    cpy_(other);
    return *this;
}

ArrayContainer ArrayContainer::fromString(const std::string& str){
    ArrayContainer arrayContainer;

    arrayContainer.data_ = arrayContainer.stringToCharArr_(str);
    arrayContainer.size_ = str.size();

    return arrayContainer;
}

const char* ArrayContainer::getData() const{
    return data_;
}
ArrayContainer::SizeType ArrayContainer::getSize() const{
    return size_;
}

void ArrayContainer::free_(){
    size_ = 0;
    if (data_ == NULL) return;
    delete[] data_;
}
void ArrayContainer::cpy_(const ArrayContainer& other){
    free_();
    size_ = other.size_;
    data_ = new char[other.size_];

    for (SizeType i = 0; i < other.size_; i++){
        data_[i] = other.data_[i];
    }
}
char* ArrayContainer::stringToCharArr_(const std::string& str){
    char* arr = new char[str.size() + 1];
    
    size_t i = 0;
    while (i < str.size()){
        arr[i] = str[i];
        i++;
    }
    arr[i] = '\0';

    return arr;
}

}
}
