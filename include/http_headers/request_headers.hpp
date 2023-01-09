#pragma once

#include "utils.hpp"
#include "common_headers.hpp"

namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{

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
    typedef MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_VERSION   HttpVersionType;
    typedef std::string                                     AcceptType;
    typedef std::string                                     AcceptCharsetType;
    typedef std::string                                     AcceptEncodingType;
    typedef std::string                                     AcceptLanguageType;
    typedef std::string                                     AuthorizationType;
    typedef std::string                                     ExpectType;
    typedef std::string                                     FromType;
    typedef std::string                                     HostType;
    typedef std::string                                     IfMatchType;
    typedef std::string                                     IfModifiedSinceType;
    typedef std::string                                     IfNoneMatchType;
    typedef std::string                                     IfRangeType;
    typedef std::string                                     IfUnmodifiedSinceType;
    typedef std::string                                     MaxForwardsType;
    typedef std::string                                     ProxyAuthorizationType;
    typedef std::string                                     RangeType;
    typedef std::string                                     RefererType;
    typedef std::string                                     TEType;
    typedef std::string                                     UserAgentType;

    HttpRequestHeaders(const HttpRequestStatusLine& statusLine);
    HttpRequestHeaders(const HttpRequestHeaders& other);
    ~HttpRequestHeaders();

    HttpRequestHeaders& operator=(const HttpRequestHeaders& other);

    void setAccept(const AcceptType& accept);
    AcceptType& getAccept();
    const AcceptType& getAccept() const;

    void setAcceptCharset(const AcceptCharsetType& acceptCharset);
    AcceptCharsetType& getAcceptCharset();
    const AcceptCharsetType& getAcceptCharset() const;

    void setAcceptEncoding(const AcceptEncodingType& acceptEncoding);
    AcceptEncodingType& getAcceptEncoding();
    const AcceptEncodingType& getAcceptEncoding() const;

    void setAcceptLanguage(const AcceptLanguageType& acceptLanguage);
    AcceptLanguageType& getAcceptLanguage();
    const AcceptLanguageType& getAcceptLanguage() const;

    void setAuthorization(const AuthorizationType& authorization);
    AuthorizationType& getAuthorization();
    const AuthorizationType& getAuthorization() const;

    void setExpect(const ExpectType& expect);
    ExpectType& getExpect();
    const ExpectType& getExpect() const;

    void setFrom(const FromType& from);
    FromType& getFrom();
    const FromType& getFrom() const;

    void setHost(const HostType& host);
    HostType& getHost();
    const HostType& getHost() const;

    void setIfMatch(const IfMatchType& ifMatch);
    IfMatchType& getIfMatch();
    const IfMatchType& getIfMatch() const;

    void setIfModifiedSince(const IfModifiedSinceType& ifModifiedSince);
    IfModifiedSinceType& getIfModifiedSince();
    const IfModifiedSinceType& getIfModifiedSince() const;

    void setIfNoneMatch(const IfNoneMatchType& ifNoneMatch);
    IfNoneMatchType& getIfNoneMatch();
    const IfNoneMatchType& getIfNoneMatch() const;

    void setIfRange(const IfRangeType& ifRange);
    IfRangeType& getIfRange();
    const IfRangeType& getIfRange() const;

    void setIfUnmodifiedSince(const IfUnmodifiedSinceType& ifUnmodifiedSince);
    IfUnmodifiedSinceType& getIfUnmodifiedSince();
    const IfUnmodifiedSinceType& getIfUnmodifiedSince() const;

    void setMaxForwards(const MaxForwardsType& maxForwards);
    MaxForwardsType& getMaxForwards();
    const MaxForwardsType& getMaxForwards() const;

    void setProxyAuthorization(const ProxyAuthorizationType& proxyAuthorization);
    ProxyAuthorizationType& getProxyAuthorization();
    const ProxyAuthorizationType& getProxyAuthorization() const;

    void setRange(const RangeType& range);
    RangeType& getRange();
    const RangeType& getRange() const;

    void setReferer(const RefererType& refer);
    RefererType& getReferer();
    const RefererType& getReferer() const;

    void setTE(const TEType& TE);
    TEType& getTE();
    const TEType& getTE() const;

    void setUserAgent(const UserAgentType& userAgent);
    UserAgentType& getUserAgent();
    const UserAgentType& getUserAgent() const;

private:
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<AcceptType> accept_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<AcceptCharsetType> acceptCharset_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<AcceptEncodingType> acceptEncoding_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<AcceptLanguageType> acceptLanguage_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<AuthorizationType> authorization_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ExpectType> expect_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<FromType> from_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<HostType> host_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<IfMatchType> ifMatch_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<IfModifiedSinceType> ifModifiedSince_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<IfNoneMatchType> ifNoneMatch_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<IfRangeType> ifRange_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<IfUnmodifiedSinceType> ifUnmodifiedSince_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<MaxForwardsType> maxForwards_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ProxyAuthorizationType> proxyAuthorization_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<RangeType> range_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<RefererType> referer_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<TEType> TE_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<UserAgentType> userAgent_;

    void deleteData_();
    void copyData_(const ParserAbstractParent& o);
    void checkValidity_() const;
    void throwOnDone_() const;

};

}
