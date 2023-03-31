#pragma once

#include "utils.hpp"
#include "common_headers.hpp"

namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{

class HttpRequestHeadersException : public MAIN_NAMESPACE::UTILS_NAMESPACE::Exception {
public:
    HttpRequestHeadersException(const char* msg);
    HttpRequestHeadersException(const std::string& msg);

    HttpRequestHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    HttpRequestHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    HttpRequestHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    HttpRequestHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    virtual std::string output_() const;

};


class HttpRequestHeaders : public HttpCommonHeaders{
public:
    typedef HttpRequestHeadersException                     ExceptionType;

    HttpRequestHeaders(const StatusLineAbstractParent& statusLine);
    HttpRequestHeaders(const HttpRequestHeaders& other);
    ~HttpRequestHeaders();

    HttpRequestHeaders& operator=(const HttpRequestHeaders& other);

    void setAccept(const std::string& accept);
    std::string& getAccept();
    const std::string& getAccept() const;

    void setAcceptCharset(const std::string& acceptCharset);
    std::string& getAcceptCharset();
    const std::string& getAcceptCharset() const;

    void setAcceptEncoding(const std::string& acceptEncoding);
    std::string& getAcceptEncoding();
    const std::string& getAcceptEncoding() const;

    void setAcceptLanguage(const std::string& acceptLanguage);
    std::string& getAcceptLanguage();
    const std::string& getAcceptLanguage() const;

    void setAuthorization(const std::string& authorization);
    std::string& getAuthorization();
    const std::string& getAuthorization() const;

    void setExpect(const std::string& expect);
    std::string& getExpect();
    const std::string& getExpect() const;

    void setFrom(const std::string& from);
    std::string& getFrom();
    const std::string& getFrom() const;

    void setHost(const std::string& host);
    std::string& getHost();
    const std::string& getHost() const;

    void setIfMatch(const std::string& ifMatch);
    std::string& getIfMatch();
    const std::string& getIfMatch() const;

    void setIfModifiedSince(const std::string& ifModifiedSince);
    std::string& getIfModifiedSince();
    const std::string& getIfModifiedSince() const;

    void setIfNoneMatch(const std::string& ifNoneMatch);
    std::string& getIfNoneMatch();
    const std::string& getIfNoneMatch() const;

    void setIfRange(const std::string& ifRange);
    std::string& getIfRange();
    const std::string& getIfRange() const;

    void setIfUnmodifiedSince(const std::string& ifUnmodifiedSince);
    std::string& getIfUnmodifiedSince();
    const std::string& getIfUnmodifiedSince() const;

    void setMaxForwards(const std::string& maxForwards);
    std::string& getMaxForwards();
    const std::string& getMaxForwards() const;

    void setProxyAuthorization(const std::string& proxyAuthorization);
    std::string& getProxyAuthorization();
    const std::string& getProxyAuthorization() const;

    void setRange(const std::string& range);
    std::string& getRange();
    const std::string& getRange() const;

    void setReferer(const std::string& refer);
    std::string& getReferer();
    const std::string& getReferer() const;

    void setTE(const std::string& TE);
    std::string& getTE();
    const std::string& getTE() const;

    void setUserAgent(const std::string& userAgent);
    std::string& getUserAgent();
    const std::string& getUserAgent() const;

private:
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> accept_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> acceptCharset_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> acceptEncoding_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> acceptLanguage_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> authorization_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> expect_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> from_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> host_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> ifMatch_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> ifModifiedSince_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> ifNoneMatch_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> ifRange_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> ifUnmodifiedSince_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> maxForwards_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> proxyAuthorization_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> range_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> referer_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> TE_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> userAgent_;

    void deleteData_();
    void copyData_(const ParserAbstractParent& o);
    void checkValidity_() const;
    void throwOnDone_() const;

};

}
}
