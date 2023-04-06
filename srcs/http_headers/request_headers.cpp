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

void HttpRequestHeaders::setAccept(const std::string& accept){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    accept_.set(accept);
}
std::string& HttpRequestHeaders::getAccept(){
    HANDLE_EXC_BEGIN
        return accept_.get();
    HANDLE_EXC_END
}
const std::string& HttpRequestHeaders::getAccept() const{
    HANDLE_EXC_BEGIN
        return accept_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setAcceptCharset(const std::string& acceptCharset){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    acceptCharset_.set(acceptCharset);
}
std::string& HttpRequestHeaders::getAcceptCharset(){
    HANDLE_EXC_BEGIN
        return acceptCharset_.get();
    HANDLE_EXC_END
}
const std::string& HttpRequestHeaders::getAcceptCharset() const{
    HANDLE_EXC_BEGIN
        return acceptCharset_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setAcceptEncoding(const std::string& acceptEncoding){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    acceptEncoding_.set(acceptEncoding);
}
std::string& HttpRequestHeaders::getAcceptEncoding(){
    HANDLE_EXC_BEGIN
        return acceptEncoding_.get();
    HANDLE_EXC_END
}
const std::string& HttpRequestHeaders::getAcceptEncoding() const{
    HANDLE_EXC_BEGIN
        return acceptEncoding_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setAcceptLanguage(const std::string& acceptLanguage){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    acceptLanguage_.set(acceptLanguage);
}
std::string& HttpRequestHeaders::getAcceptLanguage(){
    HANDLE_EXC_BEGIN
        return acceptLanguage_.get();
    HANDLE_EXC_END
}
const std::string& HttpRequestHeaders::getAcceptLanguage() const{
    HANDLE_EXC_BEGIN
        return acceptLanguage_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setAuthorization(const std::string& authorization){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_AUTH);
    authorization_.set(authorization);
}
std::string& HttpRequestHeaders::getAuthorization(){
    HANDLE_EXC_BEGIN
        return authorization_.get();
    HANDLE_EXC_END
}
const std::string& HttpRequestHeaders::getAuthorization() const{
    HANDLE_EXC_BEGIN
        return authorization_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setExpect(const std::string& expect){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1v2);
    expect_.set(expect);
}
std::string& HttpRequestHeaders::getExpect(){
    HANDLE_EXC_BEGIN
        return expect_.get();
    HANDLE_EXC_END
}
const std::string& HttpRequestHeaders::getExpect() const{
    HANDLE_EXC_BEGIN
        return expect_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setFrom(const std::string& from){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    from_.set(from);
}
std::string& HttpRequestHeaders::getFrom(){
    HANDLE_EXC_BEGIN
        return from_.get();
    HANDLE_EXC_END
}
const std::string& HttpRequestHeaders::getFrom() const{
    HANDLE_EXC_BEGIN
        return from_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setHost(const std::string& host){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    host_.set(host);
}
std::string& HttpRequestHeaders::getHost(){
    HANDLE_EXC_BEGIN
        return host_.get();
    HANDLE_EXC_END
}
const std::string& HttpRequestHeaders::getHost() const{
    HANDLE_EXC_BEGIN
        return host_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setIfMatch(const std::string& ifMatch){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    ifMatch_.set(ifMatch);
}
std::string& HttpRequestHeaders::getIfMatch(){
    HANDLE_EXC_BEGIN
        return ifMatch_.get();
    HANDLE_EXC_END
}
const std::string& HttpRequestHeaders::getIfMatch() const{
    HANDLE_EXC_BEGIN
        return host_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setIfModifiedSince(const std::string& ifModifiedSince){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    ifModifiedSince_.set(ifModifiedSince);
}
std::string& HttpRequestHeaders::getIfModifiedSince(){
    HANDLE_EXC_BEGIN
        return ifModifiedSince_.get();
    HANDLE_EXC_END
}
const std::string& HttpRequestHeaders::getIfModifiedSince() const{
    HANDLE_EXC_BEGIN
        return ifModifiedSince_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setIfNoneMatch(const std::string& ifNoneMatch){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    ifNoneMatch_.set(ifNoneMatch);
}
std::string& HttpRequestHeaders::getIfNoneMatch(){
    HANDLE_EXC_BEGIN
        return ifNoneMatch_.get();
    HANDLE_EXC_END
}
const std::string& HttpRequestHeaders::getIfNoneMatch() const{
    HANDLE_EXC_BEGIN
        return ifNoneMatch_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setIfRange(const std::string& ifRange){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    ifRange_.set(ifRange);
}
std::string& HttpRequestHeaders::getIfRange(){
    HANDLE_EXC_BEGIN
        return ifRange_.get();
    HANDLE_EXC_END
}
const std::string& HttpRequestHeaders::getIfRange() const{
    HANDLE_EXC_BEGIN
        return ifRange_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setIfUnmodifiedSince(const std::string& ifUnmodifiedSince){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    ifUnmodifiedSince_.set(ifUnmodifiedSince);
}
std::string& HttpRequestHeaders::getIfUnmodifiedSince(){
    HANDLE_EXC_BEGIN
        return ifUnmodifiedSince_.get();
    HANDLE_EXC_END
}
const std::string& HttpRequestHeaders::getIfUnmodifiedSince() const{
    HANDLE_EXC_BEGIN
        return ifUnmodifiedSince_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setMaxForwards(const std::string& maxForwards){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    maxForwards_.set(maxForwards);
}
std::string& HttpRequestHeaders::getMaxForwards(){
    HANDLE_EXC_BEGIN
        return maxForwards_.get();
    HANDLE_EXC_END
}
const std::string& HttpRequestHeaders::getMaxForwards() const{
    HANDLE_EXC_BEGIN
        return maxForwards_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setProxyAuthorization(const std::string& proxyAuthorization){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_AUTH);
    proxyAuthorization_.set(proxyAuthorization);
}
std::string& HttpRequestHeaders::getProxyAuthorization(){
    HANDLE_EXC_BEGIN
        return proxyAuthorization_.get();
    HANDLE_EXC_END
}
const std::string& HttpRequestHeaders::getProxyAuthorization() const{
    HANDLE_EXC_BEGIN
        return proxyAuthorization_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setRange(const std::string& range){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    range_.set(range);
}
std::string& HttpRequestHeaders::getRange(){
    HANDLE_EXC_BEGIN
        return range_.get();
    HANDLE_EXC_END
}
const std::string& HttpRequestHeaders::getRange() const{
    HANDLE_EXC_BEGIN
        return range_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setReferer(const std::string& refer){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    referer_.set(refer);
}
std::string& HttpRequestHeaders::getReferer(){
    HANDLE_EXC_BEGIN
        return referer_.get();
    HANDLE_EXC_END
}
const std::string& HttpRequestHeaders::getReferer() const{
    HANDLE_EXC_BEGIN
        return referer_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setTE(const std::string& TE){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1v2);
    TE_.set(TE);
}
std::string& HttpRequestHeaders::getTE(){
    HANDLE_EXC_BEGIN
        return TE_.get();
    HANDLE_EXC_END
}
const std::string& HttpRequestHeaders::getTE() const{
    HANDLE_EXC_BEGIN
        return TE_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setUserAgent(const std::string& userAgent){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    userAgent_.set(userAgent);
}
std::string& HttpRequestHeaders::getUserAgent(){
    HANDLE_EXC_BEGIN
        return userAgent_.get();
    HANDLE_EXC_END
}
const std::string& HttpRequestHeaders::getUserAgent() const{
    HANDLE_EXC_BEGIN
        return userAgent_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::deleteData_(){
    accept_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    acceptCharset_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    acceptEncoding_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    acceptLanguage_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    authorization_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    expect_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    from_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    host_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    ifMatch_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    ifModifiedSince_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    ifNoneMatch_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    ifRange_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    ifUnmodifiedSince_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    maxForwards_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    proxyAuthorization_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    range_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    referer_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    TE_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    userAgent_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
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