#pragma once

#include <string>
#include <cstdlib>
#include <iostream>
#include <algorithm>

#define wsrv            MAIN_NAMESPACE
#define configuration   CONFIG_NAMESPACE
#define http_headers    HTTP_HEADERS_NAMESPACE
#define http_request    HTTP_REQUEST_PARS_NAMESPACE
#define http_response   HTTP_RESPONSE_GENER_NAMESPACE
#define utils           UTILS_NAMESPACE

namespace MAIN_NAMESPACE::UTILS_NAMESPACE{

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

const std::string DEFAULT_SERVER_PATH = "DefaultServer";
const std::string DEFAULT_SERVER_CONFIG_FILE_PATH = DEFAULT_SERVER_PATH + "/ConfigFile.txt";

enum MSG_TYPE {
    DEBUG,
    INFO,
    WARNING,
    ERROR
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

void        utilsPrintMsg(const std::string& msg, MSG_TYPE msgType);
void        utilsCheckArgsCount(int argc);

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
