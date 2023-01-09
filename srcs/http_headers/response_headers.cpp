#include "../../include/http_headers/response_headers.hpp"

namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{
HttpResponseHeadersException::HttpResponseHeadersException(const char* msg) : Exception(msg){}
HttpResponseHeadersException::HttpResponseHeadersException(const std::string& msg) : Exception(msg){}
HttpResponseHeadersException::HttpResponseHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpResponseHeadersException::HttpResponseHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpResponseHeadersException::HttpResponseHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
HttpResponseHeadersException::HttpResponseHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string HttpResponseHeadersException::output_() const {
    return "HTTP_RESPONSE_HEADERS_EXCEPTION: " + msg_;
}
}


namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{
HttpResponseHeaders::HttpResponseHeaders(const HttpRequestStatusLine& statusLine)
    : HttpCommonHeaders(statusLine) {

}
HttpResponseHeaders::HttpResponseHeaders(const HttpResponseHeaders& other)
    : HttpCommonHeaders(other.statusLine_) {
    copyData_(other);
}
HttpResponseHeaders::~HttpResponseHeaders(){
    deleteData_();
}

HttpResponseHeaders& HttpResponseHeaders::operator=(const HttpResponseHeaders& other){
    deleteData_();
    copyData_(other);
    return *this;
}

void HttpResponseHeaders::setAcceptRanges(const AcceptRangesType& acceptRange){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    acceptRange_.set(acceptRange);
}
HttpResponseHeaders::AcceptRangesType& HttpResponseHeaders::getAcceptRanges(){
    HANDLE_EXC_BEGIN
        return acceptRange_.get();
    HANDLE_EXC_END
}
const HttpResponseHeaders::AcceptRangesType& HttpResponseHeaders::getAcceptRanges() const{
    HANDLE_EXC_BEGIN
        return acceptRange_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::setAge(const AgeType& age){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    age_.set(age);
}
HttpResponseHeaders::AgeType& HttpResponseHeaders::getAge(){
    HANDLE_EXC_BEGIN
        return age_.get();
    HANDLE_EXC_END
}
const HttpResponseHeaders::AgeType& HttpResponseHeaders::getAge() const{
    HANDLE_EXC_BEGIN
        return age_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::setAllow(const AllowType& allow){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    allow_.set(allow);
}
HttpResponseHeaders::AllowType& HttpResponseHeaders::getAllow(){
    HANDLE_EXC_BEGIN
        return allow_.get();
    HANDLE_EXC_END
}
const HttpResponseHeaders::AllowType& HttpResponseHeaders::getAllow() const{
    HANDLE_EXC_BEGIN
        return allow_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::setAlternates(const AlternatesType& alternates){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    alternates_.set(alternates);
}
HttpResponseHeaders::AlternatesType& HttpResponseHeaders::getAlternates(){
    HANDLE_EXC_BEGIN
        return alternates_.get();
    HANDLE_EXC_END
}
const HttpResponseHeaders::AlternatesType& HttpResponseHeaders::getAlternates() const{
    HANDLE_EXC_BEGIN
        return alternates_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::setETag(const ETagType& etag){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    etag_.set(etag);
}
HttpResponseHeaders::ETagType& HttpResponseHeaders::getETag(){
    HANDLE_EXC_BEGIN
        return etag_.get();
    HANDLE_EXC_END
}
const HttpResponseHeaders::ETagType& HttpResponseHeaders::getETag() const{
    HANDLE_EXC_BEGIN
        return etag_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::setLocation(const LocationType& location){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    location_.set(location);
}
HttpResponseHeaders::LocationType& HttpResponseHeaders::getLocation(){
    HANDLE_EXC_BEGIN
        return location_.get();
    HANDLE_EXC_END
}
const HttpResponseHeaders::LocationType& HttpResponseHeaders::getLocation() const{
    HANDLE_EXC_BEGIN
        return location_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::setProxyAuthenticate(const ProxyAuthenticateType& proxyAuthenticate){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_AUTH);
    proxyAuthenticate_.set(proxyAuthenticate);
}
HttpResponseHeaders::ProxyAuthenticateType& HttpResponseHeaders::getProxyAuthenticate(){
    HANDLE_EXC_BEGIN
        return proxyAuthenticate_.get();
    HANDLE_EXC_END
}
const HttpResponseHeaders::ProxyAuthenticateType& HttpResponseHeaders::getProxyAuthenticate() const{
    HANDLE_EXC_BEGIN
        return proxyAuthenticate_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::setPublic(const PublicType& Public){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    public_.set(Public);
}
HttpResponseHeaders::PublicType& HttpResponseHeaders::getPublic(){
    HANDLE_EXC_BEGIN
        return public_.get();
    HANDLE_EXC_END
}
const HttpResponseHeaders::PublicType& HttpResponseHeaders::getPublic() const{
    HANDLE_EXC_BEGIN
        return public_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::setRetryAfter(const RetryAfterType& retryAfter){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    retryAfter_.set(retryAfter);
}
HttpResponseHeaders::RetryAfterType& HttpResponseHeaders::getRetryAfter(){
    HANDLE_EXC_BEGIN
        return retryAfter_.get();
    HANDLE_EXC_END
}
const HttpResponseHeaders::RetryAfterType& HttpResponseHeaders::getRetryAfter() const{
    HANDLE_EXC_BEGIN
        return retryAfter_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::setServer(const ServerType& server){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    server_.set(server);
}
HttpResponseHeaders::ServerType& HttpResponseHeaders::getServer(){
    HANDLE_EXC_BEGIN
        return server_.get();
    HANDLE_EXC_END
}
const HttpResponseHeaders::ServerType& HttpResponseHeaders::getServer() const{
    HANDLE_EXC_BEGIN
        return server_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::setVary(const VaryType& vary){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    vary_.set(vary);
}
HttpResponseHeaders::VaryType& HttpResponseHeaders::getVary(){
    HANDLE_EXC_BEGIN
        return vary_.get();
    HANDLE_EXC_END
}
const HttpResponseHeaders::VaryType& HttpResponseHeaders::getVary() const{
    HANDLE_EXC_BEGIN
        return vary_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::setWWWAuthenticate(const WWWAuthenticateType& wwwAuthenticate){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_AUTH);
    wwwAuthenticate_.set(wwwAuthenticate);
}
HttpResponseHeaders::WWWAuthenticateType& HttpResponseHeaders::getWWWAuthenticate(){
    HANDLE_EXC_BEGIN
        return wwwAuthenticate_.get();
    HANDLE_EXC_END
}
const HttpResponseHeaders::WWWAuthenticateType& HttpResponseHeaders::getWWWAuthenticate() const{
    HANDLE_EXC_BEGIN
        return wwwAuthenticate_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::deleteData_(){
    acceptRange_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<AcceptRangesType>();
    age_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<AgeType>();
    allow_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<AllowType>();
    alternates_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<AlternatesType>();
    etag_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ETagType>();
    location_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<LocationType>();
    proxyAuthenticate_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ProxyAuthenticateType>();
    public_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<PublicType>();
    retryAfter_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<RetryAfterType>();
    server_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ServerType>();
    vary_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<VaryType>();
    wwwAuthenticate_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<WWWAuthenticateType>();
}
void HttpResponseHeaders::copyData_(const ParserAbstractParent& o){
    const HttpResponseHeaders& other = dynamic_cast<const HttpResponseHeaders&>(o);
    
    acceptRange_ = other.acceptRange_;
    age_ = other.age_;
    allow_ = other.allow_;
    alternates_ = other.alternates_;
    etag_ = other.etag_;
    location_ = other.location_;
    proxyAuthenticate_ = other.proxyAuthenticate_;
    public_ = other.public_;
    retryAfter_ = other.retryAfter_;
    server_ = other.server_;
    vary_ = other.vary_;
    wwwAuthenticate_ = other.wwwAuthenticate_;
}
void HttpResponseHeaders::checkValidity_() const{
    
}
void HttpResponseHeaders::throwOnDone_() const{
    if (isDone_) throw ExceptionType("Response headers are done. You cannot change it anymore");
}
}
