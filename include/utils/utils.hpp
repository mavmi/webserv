#pragma once

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>

#define MAIN_NAMESPACE                  wsrv
#define CONFIG_NAMESPACE                configuration
#define HTTP_HEADERS_NAMESPACE          http_headers
#define HTTP_REQUEST_PARS_NAMESPACE     http_request
#define HTTP_RESPONSE_GENER_NAMESPACE   http_response
#define UTILS_NAMESPACE                 utils

namespace MAIN_NAMESPACE{
namespace UTILS_NAMESPACE{

const size_t BUFFER_SIZE = 32;
const std::string DEFAULT_SERVER_PATH = "DefaultServer";
const std::string DEFAULT_SERVER_CONFIG_FILE_PATH = DEFAULT_SERVER_PATH + "/ConfigFile.txt";

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

class BytesContainer{
public:
    BytesContainer();
    BytesContainer(const BytesContainer& other);
    ~BytesContainer();

    BytesContainer& operator=(const BytesContainer& other);

    void pushBack(const std::string& line);

    std::vector<char*> bytesContainer;
    const size_t bufferSize;
    size_t lastSize;

private:
    void cpy_(const BytesContainer& other);
    char* realloc_(char* buffer, size_t bufferSize);
    void free_();

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

}
}
