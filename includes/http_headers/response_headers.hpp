#pragma once

#include "utils.hpp"
#include "common_headers.hpp"

namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{

class HttpResponseHeadersException : public MAIN_NAMESPACE::UTILS_NAMESPACE::Exception {
public:
    HttpResponseHeadersException(const char* msg);
    HttpResponseHeadersException(const std::string& msg);

    HttpResponseHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    HttpResponseHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    HttpResponseHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    HttpResponseHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    virtual std::string output_() const;

};


class HttpResponseHeaders : public HttpCommonHeaders{
public:
    typedef HttpResponseHeadersException    ExceptionType;

    HttpResponseHeaders(const StatusLineAbstractParent& statusLine);
    HttpResponseHeaders(const HttpResponseHeaders& other);
    ~HttpResponseHeaders();

    HttpResponseHeaders& operator=(const HttpResponseHeaders& other);

    void setAcceptRanges(const std::string& acceptRange);
    std::string& getAcceptRanges();
    const std::string& getAcceptRanges() const;

    void setAge(const std::string& age);
    std::string& getAge();
    const std::string& getAge() const;

    void setAllow(const std::string& allow);
    std::string& getAllow();
    const std::string& getAllow() const;

    void setAlternates(const std::string& alternates);
    std::string& getAlternates();
    const std::string& getAlternates() const;

    void setETag(const std::string& etag);
    std::string& getETag();
    const std::string& getETag() const;

    void setLocation(const std::string& location);
    std::string& getLocation();
    const std::string& getLocation() const;

    void setProxyAuthenticate(const std::string& proxyAuthenticate);
    std::string& getProxyAuthenticate();
    const std::string& getProxyAuthenticate() const;

    void setPublic(const std::string& Public);
    std::string& getPublic();
    const std::string& getPublic() const;

    void setRetryAfter();
    void setRetryAfter(const std::string& retryAfter);
    std::string& getRetryAfter();
    const std::string& getRetryAfter() const;

    void setServer();
    void setServer(const std::string& server);
    std::string& getServer();
    const std::string& getServer() const;

    void setVary(const std::string& vary);
    std::string& getVary();
    const std::string& getVary() const;

    void setWWWAuthenticate(const std::string& wwwAuthenticate);
    std::string& getWWWAuthenticate();
    const std::string& getWWWAuthenticate() const;

private:
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> acceptRange_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> age_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> allow_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> alternates_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> etag_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> location_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> proxyAuthenticate_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> public_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> retryAfter_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> server_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> vary_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> wwwAuthenticate_;

    void deleteData_();
    void copyData_(const ParserAbstractParent& o);
    void checkValidity_() const;
    void throwOnDone_() const;

};

}
}
