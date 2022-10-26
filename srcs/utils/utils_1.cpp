#include "../../include/utils.hpp"

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
    if (argc != 2){
        utilsPrintMsg("configuration file required", ERROR);
        exit(1);
    }
}

int utilsStringToInt(const std::string& str){
    if (!str.size()) return 0;
    
    bool positive = true;
    int res = 0;

    size_t i = 0;
    if (str[0] == '-') {
        i++;
        positive = false;
    }

    while (i < str.size()){
        char c = str.at(i);
        if (c < '0' || c > '9') return 0;
        res = res * 10 + (c - '0');
        i++;
    }

    if (!positive) res *= -1;
    return res;
}

std::string utilsIntToString(int num){
    if (num == 0) return "0";
    
    std::string result;
    while (num > 0){
        result += '0' + num % 10;
        num /= 10;
    }

    std::reverse(result.begin(), result.end());
    return result;
}
