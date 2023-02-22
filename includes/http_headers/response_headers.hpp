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
    typedef std::string                     AcceptRangesType;
    typedef std::string                     AgeType;
    typedef std::string                     AllowType;
    typedef std::string                     AlternatesType;
    typedef std::string                     ETagType;
    typedef std::string                     LocationType;
    typedef std::string                     ProxyAuthenticateType;
    typedef std::string                     PublicType;
    typedef std::string                     RetryAfterType;
    typedef std::string                     ServerType;
    typedef std::string                     VaryType;
    typedef std::string                     WWWAuthenticateType;

    HttpResponseHeaders(const StatusLineAbstractParent& statusLine);
    HttpResponseHeaders(const HttpResponseHeaders& other);
    ~HttpResponseHeaders();

    HttpResponseHeaders& operator=(const HttpResponseHeaders& other);

    void setAcceptRanges(const AcceptRangesType& acceptRange);
    AcceptRangesType& getAcceptRanges();
    const AcceptRangesType& getAcceptRanges() const;

    void setAge(const AgeType& age);
    AgeType& getAge();
    const AgeType& getAge() const;

    void setAllow(const AllowType& allow);
    AllowType& getAllow();
    const AllowType& getAllow() const;

    void setAlternates(const AlternatesType& alternates);
    AlternatesType& getAlternates();
    const AlternatesType& getAlternates() const;

    void setETag(const ETagType& etag);
    ETagType& getETag();
    const ETagType& getETag() const;

    void setLocation(const LocationType& location);
    LocationType& getLocation();
    const LocationType& getLocation() const;

    void setProxyAuthenticate(const ProxyAuthenticateType& proxyAuthenticate);
    ProxyAuthenticateType& getProxyAuthenticate();
    const ProxyAuthenticateType& getProxyAuthenticate() const;

    void setPublic(const PublicType& Public);
    PublicType& getPublic();
    const PublicType& getPublic() const;

    void setRetryAfter(const RetryAfterType& retryAfter);
    RetryAfterType& getRetryAfter();
    const RetryAfterType& getRetryAfter() const;

    void setServer(const ServerType& server);
    ServerType& getServer();
    const ServerType& getServer() const;

    void setVary(const VaryType& vary);
    VaryType& getVary();
    const VaryType& getVary() const;

    void setWWWAuthenticate(const WWWAuthenticateType& wwwAuthenticate);
    WWWAuthenticateType& getWWWAuthenticate();
    const WWWAuthenticateType& getWWWAuthenticate() const;

private:
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<AcceptRangesType> acceptRange_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<AgeType> age_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<AllowType> allow_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<AlternatesType> alternates_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ETagType> etag_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<LocationType> location_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ProxyAuthenticateType> proxyAuthenticate_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<PublicType> public_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<RetryAfterType> retryAfter_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ServerType> server_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<VaryType> vary_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<WWWAuthenticateType> wwwAuthenticate_;

    void deleteData_();
    void copyData_(const ParserAbstractParent& o);
    void checkValidity_() const;
    void throwOnDone_() const;

};

}
}
