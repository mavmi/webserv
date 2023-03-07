#include "../../includes/http_headers/request_headers.hpp"

namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{
HttpRequestHeadersException::HttpRequestHeadersException(const char* msg) : Exception(msg){}
HttpRequestHeadersException::HttpRequestHeadersException(const std::string& msg) : Exception(msg){}
HttpRequestHeadersException::HttpRequestHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpRequestHeadersException::HttpRequestHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpRequestHeadersException::HttpRequestHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
HttpRequestHeadersException::HttpRequestHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string HttpRequestHeadersException::output_() const {
    return "HTTP_REQUEST_HEADERS_EXCEPTION: " + msg_;
}
}
}


namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{
HttpRequestHeaders::HttpRequestHeaders(const StatusLineAbstractParent& statusLine)
    : HttpCommonHeaders(statusLine) {

}
HttpRequestHeaders::HttpRequestHeaders(const HttpRequestHeaders& other)
    : HttpCommonHeaders(other.statusLine_) {
    copyData_(other);
}
HttpRequestHeaders::~HttpRequestHeaders(){
    deleteData_();
}

HttpRequestHeaders& HttpRequestHeaders::operator=(const HttpRequestHeaders& other){
    deleteData_();
    copyData_(other);
    return *this;
}

void HttpRequestHeaders::setAccept(const AcceptType& accept){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    accept_.set(accept);
}
HttpRequestHeaders::AcceptType& HttpRequestHeaders::getAccept(){
    HANDLE_EXC_BEGIN
        return accept_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::AcceptType& HttpRequestHeaders::getAccept() const{
    HANDLE_EXC_BEGIN
        return accept_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setAcceptCharset(const AcceptCharsetType& acceptCharset){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    acceptCharset_.set(acceptCharset);
}
HttpRequestHeaders::AcceptCharsetType& HttpRequestHeaders::getAcceptCharset(){
    HANDLE_EXC_BEGIN
        return acceptCharset_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::AcceptCharsetType& HttpRequestHeaders::getAcceptCharset() const{
    HANDLE_EXC_BEGIN
        return acceptCharset_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setAcceptEncoding(const AcceptEncodingType& acceptEncoding){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    acceptEncoding_.set(acceptEncoding);
}
HttpRequestHeaders::AcceptEncodingType& HttpRequestHeaders::getAcceptEncoding(){
    HANDLE_EXC_BEGIN
        return acceptEncoding_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::AcceptEncodingType& HttpRequestHeaders::getAcceptEncoding() const{
    HANDLE_EXC_BEGIN
        return acceptEncoding_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setAcceptLanguage(const AcceptLanguageType& acceptLanguage){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    acceptLanguage_.set(acceptLanguage);
}
HttpRequestHeaders::AcceptLanguageType& HttpRequestHeaders::getAcceptLanguage(){
    HANDLE_EXC_BEGIN
        return acceptLanguage_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::AcceptLanguageType& HttpRequestHeaders::getAcceptLanguage() const{
    HANDLE_EXC_BEGIN
        return acceptLanguage_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setAuthorization(const AuthorizationType& authorization){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_AUTH);
    authorization_.set(authorization);
}
HttpRequestHeaders::AuthorizationType& HttpRequestHeaders::getAuthorization(){
    HANDLE_EXC_BEGIN
        return authorization_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::AuthorizationType& HttpRequestHeaders::getAuthorization() const{
    HANDLE_EXC_BEGIN
        return authorization_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setExpect(const ExpectType& expect){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1v2);
    expect_.set(expect);
}
HttpRequestHeaders::ExpectType& HttpRequestHeaders::getExpect(){
    HANDLE_EXC_BEGIN
        return expect_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::ExpectType& HttpRequestHeaders::getExpect() const{
    HANDLE_EXC_BEGIN
        return expect_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setFrom(const FromType& from){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    from_.set(from);
}
HttpRequestHeaders::FromType& HttpRequestHeaders::getFrom(){
    HANDLE_EXC_BEGIN
        return from_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::FromType& HttpRequestHeaders::getFrom() const{
    HANDLE_EXC_BEGIN
        return from_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setHost(const HostType& host){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    host_.set(host);
}
HttpRequestHeaders::HostType& HttpRequestHeaders::getHost(){
    HANDLE_EXC_BEGIN
        return host_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::HostType& HttpRequestHeaders::getHost() const{
    HANDLE_EXC_BEGIN
        return host_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setIfMatch(const IfMatchType& ifMatch){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    ifMatch_.set(ifMatch);
}
HttpRequestHeaders::IfMatchType& HttpRequestHeaders::getIfMatch(){
    HANDLE_EXC_BEGIN
        return ifMatch_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::IfMatchType& HttpRequestHeaders::getIfMatch() const{
    HANDLE_EXC_BEGIN
        return host_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setIfModifiedSince(const IfModifiedSinceType& ifModifiedSince){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    ifModifiedSince_.set(ifModifiedSince);
}
HttpRequestHeaders::IfModifiedSinceType& HttpRequestHeaders::getIfModifiedSince(){
    HANDLE_EXC_BEGIN
        return ifModifiedSince_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::IfModifiedSinceType& HttpRequestHeaders::getIfModifiedSince() const{
    HANDLE_EXC_BEGIN
        return ifModifiedSince_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setIfNoneMatch(const IfNoneMatchType& ifNoneMatch){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    ifNoneMatch_.set(ifNoneMatch);
}
HttpRequestHeaders::IfNoneMatchType& HttpRequestHeaders::getIfNoneMatch(){
    HANDLE_EXC_BEGIN
        return ifNoneMatch_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::IfNoneMatchType& HttpRequestHeaders::getIfNoneMatch() const{
    HANDLE_EXC_BEGIN
        return ifNoneMatch_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setIfRange(const IfRangeType& ifRange){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    ifRange_.set(ifRange);
}
HttpRequestHeaders::IfRangeType& HttpRequestHeaders::getIfRange(){
    HANDLE_EXC_BEGIN
        return ifRange_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::IfRangeType& HttpRequestHeaders::getIfRange() const{
    HANDLE_EXC_BEGIN
        return ifRange_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setIfUnmodifiedSince(const IfUnmodifiedSinceType& ifUnmodifiedSince){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    ifUnmodifiedSince_.set(ifUnmodifiedSince);
}
HttpRequestHeaders::IfUnmodifiedSinceType& HttpRequestHeaders::getIfUnmodifiedSince(){
    HANDLE_EXC_BEGIN
        return ifUnmodifiedSince_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::IfUnmodifiedSinceType& HttpRequestHeaders::getIfUnmodifiedSince() const{
    HANDLE_EXC_BEGIN
        return ifUnmodifiedSince_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setMaxForwards(const MaxForwardsType& maxForwards){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    maxForwards_.set(maxForwards);
}
HttpRequestHeaders::MaxForwardsType& HttpRequestHeaders::getMaxForwards(){
    HANDLE_EXC_BEGIN
        return maxForwards_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::MaxForwardsType& HttpRequestHeaders::getMaxForwards() const{
    HANDLE_EXC_BEGIN
        return maxForwards_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setProxyAuthorization(const ProxyAuthorizationType& proxyAuthorization){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_AUTH);
    proxyAuthorization_.set(proxyAuthorization);
}
HttpRequestHeaders::ProxyAuthorizationType& HttpRequestHeaders::getProxyAuthorization(){
    HANDLE_EXC_BEGIN
        return proxyAuthorization_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::ProxyAuthorizationType& HttpRequestHeaders::getProxyAuthorization() const{
    HANDLE_EXC_BEGIN
        return proxyAuthorization_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setRange(const RangeType& range){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    range_.set(range);
}
HttpRequestHeaders::RangeType& HttpRequestHeaders::getRange(){
    HANDLE_EXC_BEGIN
        return range_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::RangeType& HttpRequestHeaders::getRange() const{
    HANDLE_EXC_BEGIN
        return range_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setReferer(const RefererType& refer){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    referer_.set(refer);
}
HttpRequestHeaders::RefererType& HttpRequestHeaders::getReferer(){
    HANDLE_EXC_BEGIN
        return referer_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::RefererType& HttpRequestHeaders::getReferer() const{
    HANDLE_EXC_BEGIN
        return referer_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setTE(const TEType& TE){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1v2);
    TE_.set(TE);
}
HttpRequestHeaders::TEType& HttpRequestHeaders::getTE(){
    HANDLE_EXC_BEGIN
        return TE_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::TEType& HttpRequestHeaders::getTE() const{
    HANDLE_EXC_BEGIN
        return TE_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setUserAgent(const UserAgentType& userAgent){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    userAgent_.set(userAgent);
}
HttpRequestHeaders::UserAgentType& HttpRequestHeaders::getUserAgent(){
    HANDLE_EXC_BEGIN
        return userAgent_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::UserAgentType& HttpRequestHeaders::getUserAgent() const{
    HANDLE_EXC_BEGIN
        return userAgent_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::deleteData_(){
    accept_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<AcceptType>();
    acceptCharset_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<AcceptCharsetType>();
    acceptEncoding_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<AcceptEncodingType>();
    acceptLanguage_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<AcceptLanguageType>();
    authorization_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<AuthorizationType>();
    expect_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ExpectType>();
    from_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<FromType>();
    host_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<HostType>();
    ifMatch_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<IfMatchType>();
    ifModifiedSince_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<IfModifiedSinceType>();
    ifNoneMatch_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<IfNoneMatchType>();
    ifRange_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<IfRangeType>();
    ifUnmodifiedSince_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<IfUnmodifiedSinceType>();
    maxForwards_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<MaxForwardsType>();
    proxyAuthorization_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ProxyAuthorizationType>();
    range_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<RangeType>();
    referer_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<RefererType>();
    TE_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<TEType>();
    userAgent_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<UserAgentType>();
}
void HttpRequestHeaders::copyData_(const ParserAbstractParent& o){
    const HttpRequestHeaders& other = dynamic_cast<const HttpRequestHeaders&>(o);
    
    accept_ = other.accept_;
    acceptCharset_ = other.acceptCharset_;
    acceptEncoding_ = other.acceptEncoding_;
    acceptLanguage_ = other.acceptLanguage_;
    authorization_ = other.authorization_;
    expect_ = other.expect_;
    from_ = other.from_;
    host_ = other.host_;
    ifMatch_ = other.ifMatch_;
    ifModifiedSince_ = other.ifModifiedSince_;
    ifNoneMatch_ = other.ifNoneMatch_;
    ifRange_ = other.ifRange_;
    ifUnmodifiedSince_ = other.ifUnmodifiedSince_;
    maxForwards_ = other.maxForwards_;
    proxyAuthorization_ = other.proxyAuthorization_;
    range_ = other.range_;
    referer_ = other.referer_;
    TE_ = other.TE_;
    userAgent_ = other.userAgent_;
}
void HttpRequestHeaders::checkValidity_() const{
    
}
void HttpRequestHeaders::throwOnDone_() const{
    if (isDone_) throw ExceptionType("Request headers are done. You cannot change it anymore");
}
}
}