#pragma once

#include "utils.hpp"

namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{

class HttpRequestStatusLineException : public MAIN_NAMESPACE::UTILS_NAMESPACE::Exception {
public:
    HttpRequestStatusLineException(const char* msg);
    HttpRequestStatusLineException(const std::string& msg);

    HttpRequestStatusLineException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    HttpRequestStatusLineException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    HttpRequestStatusLineException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    HttpRequestStatusLineException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    virtual std::string output_() const;

};


class HttpRequestStatusLine{
friend HttpRequestParser;
public:
    ~HttpRequestStatusLine();

private:
    /*
        Bunch of wrappers must be here
    */

    HttpRequestStatusLine();
    HttpRequestStatusLine(const HttpRequestStatusLine& other);

    HttpRequestStatusLine& operator=(const HttpRequestStatusLine& other);

};

}
