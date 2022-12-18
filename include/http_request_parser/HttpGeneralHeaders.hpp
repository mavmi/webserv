#pragma once

#include "utils.hpp"
#include "../utils/httpHeadersAbstractParent.hpp"

namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{

class HttpGeneralHeadersException : public MAIN_NAMESPACE::UTILS_NAMESPACE::Exception {
public:
    HttpGeneralHeadersException(const char* msg);
    HttpGeneralHeadersException(const std::string& msg);

    HttpGeneralHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    HttpGeneralHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    HttpGeneralHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    HttpGeneralHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    virtual std::string output_() const;

};


class HttpGeneralHeaders : public MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent, public MAIN_NAMESPACE::UTILS_NAMESPACE::HttpHeadersAbstractParent{
friend HttpRequestParser;
public:
    typedef HttpGeneralHeadersException     ExceptionType;

    ~HttpGeneralHeaders();

private:
    HttpGeneralHeaders();
    HttpGeneralHeaders(const HttpGeneralHeaders& other);

    HttpGeneralHeaders& operator=(const HttpGeneralHeaders& other);

    void deleteData_();
    void copyData_(const ParserAbstractParent& o);
    void checkValidity_() const;
    void throwOnDone_() const;

};

}
