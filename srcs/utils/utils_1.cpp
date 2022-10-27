#include "../../include/utils.hpp"


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
