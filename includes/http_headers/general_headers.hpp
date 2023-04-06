#pragma once

#include <ctime>

#include "utils.hpp"
#include "headers_abstract_parent.hpp"

namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{

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


class HttpGeneralHeaders : public MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent, public HttpHeadersAbstractParent{
public:
    typedef HttpGeneralHeadersException                     ExceptionType;

    HttpGeneralHeaders(const StatusLineAbstractParent& statusLine);
    HttpGeneralHeaders(const HttpGeneralHeaders& other);
    ~HttpGeneralHeaders();

    HttpGeneralHeaders& operator=(const HttpGeneralHeaders& other);

    void setCacheControl(const std::string& cacheControl);
    std::string& getCacheControl();
    const std::string& getCacheControl() const;

    void setConnection(const std::string& connection);
    std::string& getConnection();
    const std::string& getConnection() const;

    void setDate();
    void setDate(const std::string& date);
    std::string& getDate();
    const std::string& getDate() const;

    void setMimeVersion(const std::string& mimeVersion);
    std::string& getMimeVersion();
    const std::string& getMimeVersion() const;

    void setPragma(const std::string& pragma);
    std::string& getPragma();
    const std::string& getPragma() const;

    void setTrailer(const std::string& trailer);
    std::string& getTrailer();
    const std::string& getTrailer() const;

    void setTransferEncoding(const std::string& transferEncoding);
    std::string& getTransferEncoding();
    const std::string& getTransferEncoding() const;

    void setUpgrade(const std::string& upgrade);
    std::string& getUpgrade();
    const std::string& getUpgrade() const;

    void setVia(const std::string& via);
    std::string& getVia();
    const std::string& getVia() const;

    void setWarning(const std::string& warning);
    std::string& getWarning();
    const std::string& getWarning() const;

private:
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> cacheControl_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> connection_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> date_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> mimeVersion_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> pragma_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> trailer_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> transferEncoding_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> upgrade_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> via_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> warning_;

    void deleteData_();
    void copyData_(const ParserAbstractParent& o);
    void checkValidity_() const;
    void throwOnDone_() const;

};

}
}
