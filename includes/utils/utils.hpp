#pragma once

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>

#define MAIN_NAMESPACE                  wsrv
#define CORE                            wsrv
#define CONFIG_NAMESPACE                configuration
#define HTTP_HEADERS_NAMESPACE          http_headers
#define HTTP_REQUEST_PARS_NAMESPACE     http_request
#define HTTP_RESPONSE_GENER_NAMESPACE   http_response
#define UTILS_NAMESPACE                 utils

namespace MAIN_NAMESPACE{
namespace UTILS_NAMESPACE{

const size_t BUFFER_SIZE = 1024;
const std::string DEFAULT_SERVER_PATH = "DefaultServer";
const std::string DEFAULT_SERVER_CONFIG_FILE_PATH = "materials/config_files/valid/ConfigFile.txt";

enum MSG_TYPE {
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

enum METHOD{
    GET,
    POST,
    DELETE
};

enum HTTP_VERSION{
    HTTP_0_9,
    HTTP_1_0,
    HTTP_1_1,
    HTTP_1_1v2,
    HTTP_AUTH,
    MIME,
    MD5H,
    CDH
};

class UtilsException {
public:
    UtilsException(const char* msg);
    UtilsException(const std::string& msg);
    ~UtilsException() throw();

    virtual const std::string what() const throw();

protected:
    const std::string msg_;

    virtual std::string output_() const;
    
};

std::string     httpVersionToString(HTTP_VERSION httpVersion);
HTTP_VERSION    httpVersionFromString(const std::string& httpVersionStr);

void        utilsPrintMsg(const std::string& msg, MSG_TYPE msgType);
void        utilsCheckArgsCount(int argc);
const char* utilsStringToCharArray(const std::string& str);

template <typename Type>
std::string utilsNumToString(Type num){
    if (num == 0) return "0";

    std::string result;
    while (num > 0){
        result += '0' + num % 10;
        num /= 10;
    }

    std::reverse(result.begin(), result.end());
    return result;
}
template <typename Type>
Type        utilsStringToNum(const std::string& str){
    if (!str.size()) throw UtilsException("Empty numeric string");

    bool positive = true;
    size_t i = 0;
    if (str[0] == '-'){
        positive = false;
        i++;
    }

    Type prev = 0, res = 0;
    while (i < str.size()){
        char c = str.at(i);

        if (c < '0' || c > '9') throw UtilsException("Numeric string contains wrong symbol");
        res = res * 10 + (c - '0');
        if (res < prev) throw UtilsException("Number overflow");
        prev = res;
        i++;
    }

    if (!positive) res *= -1;
    return res;

}

class BytesContainer{
public:
    typedef std::vector<std::string> BytesContainerType;

    BytesContainer();
    BytesContainer(const BytesContainer& other);
    ~BytesContainer();

    BytesContainer& operator=(const BytesContainer& other);

    void pushBack(const std::string& line);
    void pushBack(char* buffer, int bufferSize);

    const BytesContainerType& getLines() const;
    int checkIfEnd(int bufferSize);

private:
    bool r_;
    bool n_;
    int content_;
    size_t lineToCheck_;
    size_t contentLength_;
    BytesContainerType bytesContainer_;

};

class ArrayContainer{
public:
    typedef size_t SizeType;
    
    ArrayContainer(const ArrayContainer& other);
    ~ArrayContainer();

    ArrayContainer& operator=(const ArrayContainer& other);

    static ArrayContainer fromString(const std::string& str);
    template <typename T>
    static ArrayContainer fromNum(T num){
        return fromString(utilsNumToString(num));
    }

    const char* getData() const;
    SizeType getSize() const;

private:
    char* data_;
    SizeType size_;

    ArrayContainer();

    void free_();
    void cpy_(const ArrayContainer& other);
    char* stringToCharArr_(const std::string& str);

};
}
}
