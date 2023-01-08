#pragma once

#include "utils.hpp"
#include "HtttRequestStatusLine.hpp"
#include "../utils/httpHeadersAbstractParent.hpp"

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


class HttpRequestHeaders : public MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent,
                            public MAIN_NAMESPACE::UTILS_NAMESPACE::HttpHeadersAbstractParent{
friend HttpRequestParser;
public:
    typedef HttpRequestHeadersException     ExceptionType;
    typedef std::string                     AcceptType;
    typedef std::string                     AcceptCharsetType;
    typedef std::string                     AcceptEncodingType;
    typedef std::string                     AcceptLanguageType;
    typedef std::string                     AuthorizationType;
    typedef std::string                     ContentDispositionType;
    typedef std::string                     ContentEncodingType;
    typedef std::string                     ContentLanguageType;
    typedef std::string                     ContentLengthType;
    typedef std::string                     ContentLocationType;
    typedef std::string                     ContentMD5Type;
    typedef std::string                     ContentRangeType;
    typedef std::string                     ContentType;
    typedef std::string                     ContentVersionType;
    typedef std::string                     DerivedFromType;
    typedef std::string                     ExpectType;
    typedef std::string                     ExpiresType;
    typedef std::string                     FromType;
    typedef std::string                     HostType;
    typedef std::string                     IfMatchType;
    typedef std::string                     IfModifiedSinceType;
    typedef std::string                     IfNoneMatchType;
    typedef std::string                     IfRangeType;
    typedef std::string                     IfUnmodifiedSinceType;
    typedef std::string                     LastModifiedType;
    typedef std::string                     LinkType;
    typedef std::string                     MaxForwardsType;
    typedef std::string                     ProxyAuthorizationType;
    typedef std::string                     RangeType;
    typedef std::string                     RefererType;
    typedef std::string                     TitleType;
    typedef std::string                     TEType;
    typedef std::string                     UserAgentType;

    ~HttpRequestHeaders();

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

    void setContentDisposition(const ContentDispositionType& contentDisposition);
    ContentDispositionType& getContentDisposition();
    const ContentDispositionType& getContentDisposition() const;

    void setContentEncoding(const ContentEncodingType& contentEncoding);
    ContentEncodingType& getContentEncoding();
    const ContentEncodingType& getContentEncoding() const;

    void setContentLanguage(const ContentLanguageType& contentLanguage);
    ContentLanguageType& getContentLanguage();
    const ContentLanguageType& getContentLanguage() const;

    void setContentLength(const ContentLengthType& contentLength);
    ContentLengthType& getContentLength();
    const ContentLengthType& getContentLength() const;

    void setContentLocation(const ContentLocationType& contentLocation);
    ContentLocationType& getContentLocation();
    const ContentLocationType& getContentLocation() const;

    void setContentMD5(const ContentMD5Type& contentMD5);
    ContentMD5Type& getContentMD5();
    const ContentMD5Type& getContentMD5() const;

    void setContentRange(const ContentRangeType& contentRange);
    ContentRangeType& getContentRange();
    const ContentRangeType& getContentRange() const;

    void setContentType(const ContentType& contentType);
    ContentType& getContentType();
    const ContentType& getContentType() const;

    void setContentVersion(const ContentVersionType& contentVersion);
    ContentVersionType& getContentVersion();
    const ContentVersionType& getContentVersion() const;

    void setDerivedFrom(const DerivedFromType& derivedFrom);
    DerivedFromType& getDerivedFrom();
    const DerivedFromType& getDerivedFrom() const;

    void setExpect(const ExpectType& expect);
    ExpectType& getExpect();
    const ExpectType& getExpect() const;

    void setExpires(const ExpiresType& expires);
    ExpiresType& getExpires();
    const ExpiresType& getExpires() const;

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

    void setLastModified(const LastModifiedType& lastModified);
    LastModifiedType& getLastModified();
    const LastModifiedType& getLastModified() const;

    void setLink(const LinkType& link);
    LinkType& getLink();
    const LinkType& getLink() const;

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

    void setTitle(const TitleType& title);
    TitleType& getTitle();
    const TitleType& getTitle() const;

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
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentDispositionType> contentDisposition_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentEncodingType> contentEncoding_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentLanguageType> contentLanguage_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentLengthType> contentLength_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentLocationType> contentLocation_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentMD5Type> contentMD5_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentRangeType> contentRange_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentType> contentType_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentVersionType> contentVersion_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<DerivedFromType> derivedFrom_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ExpectType> expect_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ExpiresType> expires_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<FromType> from_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<HostType> host_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<IfMatchType> ifMatch_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<IfModifiedSinceType> ifModifiedSince_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<IfNoneMatchType> ifNoneMatch_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<IfRangeType> ifRange_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<IfUnmodifiedSinceType> ifUnmodifiedSince_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<LastModifiedType> lastModified_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<LinkType> link_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<MaxForwardsType> maxForwards_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ProxyAuthorizationType> proxyAuthorization_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<RangeType> range_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<RefererType> referer_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<TitleType> title_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<TEType> TE_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<UserAgentType> userAgent_;

    HttpRequestHeaders(const HttpRequestStatusLine& statusLine);
    HttpRequestHeaders(const HttpRequestHeaders& other);

    HttpRequestHeaders& operator=(const HttpRequestHeaders& other);

    void deleteData_();
    void copyData_(const ParserAbstractParent& o);
    void checkValidity_() const;
    void throwOnDone_() const;

};

}
