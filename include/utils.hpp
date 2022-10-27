#pragma once

#include <string>
#include <cstdlib>
#include <iostream>
#include <algorithm>

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
