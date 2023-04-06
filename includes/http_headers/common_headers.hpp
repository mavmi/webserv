#pragma once

#include "utils.hpp"
#include "headers_abstract_parent.hpp"

namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{

class HttpCommonHeadersException : public MAIN_NAMESPACE::UTILS_NAMESPACE::Exception {
public:
    HttpCommonHeadersException(const char* msg);
    HttpCommonHeadersException(const std::string& msg);

    HttpCommonHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    HttpCommonHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    HttpCommonHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    HttpCommonHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    virtual std::string output_() const;

};


class HttpCommonHeaders : public MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent, public HttpHeadersAbstractParent{
public:
    typedef HttpCommonHeadersException      ExceptionType;

    HttpCommonHeaders(const StatusLineAbstractParent& statusLine);
    HttpCommonHeaders(const HttpCommonHeaders& other);
    ~HttpCommonHeaders();

    HttpCommonHeaders& operator=(const HttpCommonHeaders& other);

    std::string getFilename() const;
    void setContentDisposition(const std::string& contentDisposition);
    std::string& getContentDisposition();
    const std::string& getContentDisposition() const;

    void setContentEncoding(const std::string& contentEncoding);
    std::string& getContentEncoding();
    const std::string& getContentEncoding() const;

    void setContentLanguage(const std::string& contentLanguage);
    std::string& getContentLanguage();
    const std::string& getContentLanguage() const;

    void setContentLength(const std::string& contentLength);
    std::string& getContentLength();
    const std::string& getContentLength() const;

    void setContentLocation(const std::string& contentLocation);
    std::string& getContentLocation();
    const std::string& getContentLocation() const;

    void setContentMD5(const std::string& contentMD5);
    std::string& getContentMD5();
    const std::string& getContentMD5() const;

    void setContentRange(const std::string& contentRange);
    std::string& getContentRange();
    const std::string& getContentRange() const;

    void setContentType(const std::string& contentType);
    std::string& getContentType();
    const std::string& getContentType() const;

    void setContentVersion(const std::string& contentVersion);
    std::string& getContentVersion();
    const std::string& getContentVersion() const;

    void setDerivedFrom(const std::string& derivedFrom);
    std::string& getDerivedFrom();
    const std::string& getDerivedFrom() const;

    void setExpires(const std::string& expires);
    std::string& getExpires();
    const std::string& getExpires() const;

    void setLastModified(std::tm* time);
    void setLastModified(const std::string& lastModified);
    std::string& getLastModified();
    const std::string& getLastModified() const;

    void setLink(const std::string& link);
    std::string& getLink();
    const std::string& getLink() const;

    void setTitle(const std::string& title);
    std::string& getTitle();
    const std::string& getTitle() const;

private:
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> contentDisposition_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> contentEncoding_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> contentLanguage_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> contentLength_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> contentLocation_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> contentMD5_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> contentRange_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> contentType_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> contentVersion_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> derivedFrom_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> expires_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> lastModified_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> link_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> title_;

    void deleteData_();
    void copyData_(const ParserAbstractParent& o);
    void checkValidity_() const;
    void throwOnDone_() const;

};

}
}
