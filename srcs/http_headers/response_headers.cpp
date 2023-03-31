#include "../../includes/http_headers/response_headers.hpp"

namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{
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
}


namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{
HttpResponseHeaders::HttpResponseHeaders(const StatusLineAbstractParent& statusLine)
    : HttpCommonHeaders(statusLine) {
    setServer();
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

void HttpResponseHeaders::setAcceptRanges(const std::string& acceptRange){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    acceptRange_.set(acceptRange);
}
std::string& HttpResponseHeaders::getAcceptRanges(){
    HANDLE_EXC_BEGIN
        return acceptRange_.get();
    HANDLE_EXC_END
}
const std::string& HttpResponseHeaders::getAcceptRanges() const{
    HANDLE_EXC_BEGIN
        return acceptRange_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::setAge(const std::string& age){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    age_.set(age);
}
std::string& HttpResponseHeaders::getAge(){
    HANDLE_EXC_BEGIN
        return age_.get();
    HANDLE_EXC_END
}
const std::string& HttpResponseHeaders::getAge() const{
    HANDLE_EXC_BEGIN
        return age_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::setAllow(const std::string& allow){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    allow_.set(allow);
}
std::string& HttpResponseHeaders::getAllow(){
    HANDLE_EXC_BEGIN
        return allow_.get();
    HANDLE_EXC_END
}
const std::string& HttpResponseHeaders::getAllow() const{
    HANDLE_EXC_BEGIN
        return allow_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::setAlternates(const std::string& alternates){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    alternates_.set(alternates);
}
std::string& HttpResponseHeaders::getAlternates(){
    HANDLE_EXC_BEGIN
        return alternates_.get();
    HANDLE_EXC_END
}
const std::string& HttpResponseHeaders::getAlternates() const{
    HANDLE_EXC_BEGIN
        return alternates_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::setETag(const std::string& etag){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    etag_.set(etag);
}
std::string& HttpResponseHeaders::getETag(){
    HANDLE_EXC_BEGIN
        return etag_.get();
    HANDLE_EXC_END
}
const std::string& HttpResponseHeaders::getETag() const{
    HANDLE_EXC_BEGIN
        return etag_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::setLocation(const std::string& location){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    location_.set(location);
}
std::string& HttpResponseHeaders::getLocation(){
    HANDLE_EXC_BEGIN
        return location_.get();
    HANDLE_EXC_END
}
const std::string& HttpResponseHeaders::getLocation() const{
    HANDLE_EXC_BEGIN
        return location_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::setProxyAuthenticate(const std::string& proxyAuthenticate){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_AUTH);
    proxyAuthenticate_.set(proxyAuthenticate);
}
std::string& HttpResponseHeaders::getProxyAuthenticate(){
    HANDLE_EXC_BEGIN
        return proxyAuthenticate_.get();
    HANDLE_EXC_END
}
const std::string& HttpResponseHeaders::getProxyAuthenticate() const{
    HANDLE_EXC_BEGIN
        return proxyAuthenticate_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::setPublic(const std::string& Public){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    public_.set(Public);
}
std::string& HttpResponseHeaders::getPublic(){
    HANDLE_EXC_BEGIN
        return public_.get();
    HANDLE_EXC_END
}
const std::string& HttpResponseHeaders::getPublic() const{
    HANDLE_EXC_BEGIN
        return public_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::setRetryAfter(){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);

    std::time_t t = std::time(NULL);
    std::tm* time = std::localtime(&t);
    time->tm_sec += 3;
    mktime(time);
    retryAfter_.set(generateDate_(time));
}
void HttpResponseHeaders::setRetryAfter(const std::string& retryAfter){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    retryAfter_.set(retryAfter);
}
std::string& HttpResponseHeaders::getRetryAfter(){
    HANDLE_EXC_BEGIN
        return retryAfter_.get();
    HANDLE_EXC_END
}
const std::string& HttpResponseHeaders::getRetryAfter() const{
    HANDLE_EXC_BEGIN
        return retryAfter_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::setServer(){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    server_.set("wsrv by pmalena & msaryjo");
}
void HttpResponseHeaders::setServer(const std::string& server){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    server_.set(server);
}
std::string& HttpResponseHeaders::getServer(){
    HANDLE_EXC_BEGIN
        return server_.get();
    HANDLE_EXC_END
}
const std::string& HttpResponseHeaders::getServer() const{
    HANDLE_EXC_BEGIN
        return server_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::setVary(const std::string& vary){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    vary_.set(vary);
}
std::string& HttpResponseHeaders::getVary(){
    HANDLE_EXC_BEGIN
        return vary_.get();
    HANDLE_EXC_END
}
const std::string& HttpResponseHeaders::getVary() const{
    HANDLE_EXC_BEGIN
        return vary_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::setWWWAuthenticate(const std::string& wwwAuthenticate){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_AUTH);
    wwwAuthenticate_.set(wwwAuthenticate);
}
std::string& HttpResponseHeaders::getWWWAuthenticate(){
    HANDLE_EXC_BEGIN
        return wwwAuthenticate_.get();
    HANDLE_EXC_END
}
const std::string& HttpResponseHeaders::getWWWAuthenticate() const{
    HANDLE_EXC_BEGIN
        return wwwAuthenticate_.get();
    HANDLE_EXC_END
}

void HttpResponseHeaders::deleteData_(){
    acceptRange_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    age_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    allow_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    alternates_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    etag_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    location_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    proxyAuthenticate_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    public_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    retryAfter_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    server_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    vary_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    wwwAuthenticate_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
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
}
