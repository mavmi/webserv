#include "../../includes/http_headers/common_headers.hpp"

namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{
HttpCommonHeadersException::HttpCommonHeadersException(const char* msg) : Exception(msg){}
HttpCommonHeadersException::HttpCommonHeadersException(const std::string& msg) : Exception(msg){}
HttpCommonHeadersException::HttpCommonHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpCommonHeadersException::HttpCommonHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpCommonHeadersException::HttpCommonHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
HttpCommonHeadersException::HttpCommonHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string HttpCommonHeadersException::output_() const {
    return "HTTP_COMMON_HEADERS_EXCEPTION: " + msg_;
}
}
}


namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{
HttpCommonHeaders::HttpCommonHeaders(const StatusLineAbstractParent& statusLine)
    : HttpHeadersAbstractParent(statusLine) {

}
HttpCommonHeaders::HttpCommonHeaders(const HttpCommonHeaders& other)
    : ParserAbstractParent(other), HttpHeadersAbstractParent(other.statusLine_){
    copyData_(other);
}
HttpCommonHeaders::~HttpCommonHeaders(){
    deleteData_();
}

HttpCommonHeaders& HttpCommonHeaders::operator=(const HttpCommonHeaders& other){
    deleteData_();
    copyData_(other);
    return *this;
}

void HttpCommonHeaders::setContentDisposition(const std::string& contentDisposition){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::CDH);
    contentDisposition_.set(contentDisposition);
}
std::string& HttpCommonHeaders::getContentDisposition(){
    HANDLE_EXC_BEGIN
        return contentDisposition_.get();
    HANDLE_EXC_END
}
const std::string& HttpCommonHeaders::getContentDisposition() const{
    HANDLE_EXC_BEGIN
        return contentDisposition_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setContentEncoding(const std::string& contentEncoding){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    contentEncoding_.set(contentEncoding);
}
std::string& HttpCommonHeaders::getContentEncoding(){
    HANDLE_EXC_BEGIN
        return contentEncoding_.get();
    HANDLE_EXC_END
}
const std::string& HttpCommonHeaders::getContentEncoding() const{
    HANDLE_EXC_BEGIN
        return contentEncoding_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setContentLanguage(const std::string& contentLanguage){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    contentLanguage_.set(contentLanguage);
}
std::string& HttpCommonHeaders::getContentLanguage(){
    HANDLE_EXC_BEGIN
        return contentLanguage_.get();
    HANDLE_EXC_END
}
const std::string& HttpCommonHeaders::getContentLanguage() const{
    HANDLE_EXC_BEGIN
        return contentLanguage_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setContentLength(const std::string& contentLength){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    contentLength_.set(contentLength);
}
std::string& HttpCommonHeaders::getContentLength(){
    HANDLE_EXC_BEGIN
        return contentLength_.get();
    HANDLE_EXC_END
}
const std::string& HttpCommonHeaders::getContentLength() const{
    HANDLE_EXC_BEGIN
        return contentLength_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setContentLocation(const std::string& contentLocation){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    contentLocation_.set(contentLocation);
}
std::string& HttpCommonHeaders::getContentLocation(){
    HANDLE_EXC_BEGIN
        return contentLocation_.get();
    HANDLE_EXC_END
}
const std::string& HttpCommonHeaders::getContentLocation() const{
    HANDLE_EXC_BEGIN
        return contentLocation_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setContentMD5(const std::string& contentMD5){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::MD5H);
    contentMD5_.set(contentMD5);
}
std::string& HttpCommonHeaders::getContentMD5(){
    HANDLE_EXC_BEGIN
        return contentMD5_.get();
    HANDLE_EXC_END
}
const std::string& HttpCommonHeaders::getContentMD5() const{
    HANDLE_EXC_BEGIN
        return contentMD5_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setContentRange(const std::string& contentRange){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    contentRange_.set(contentRange);
}
std::string& HttpCommonHeaders::getContentRange(){
    HANDLE_EXC_BEGIN
        return contentRange_.get();
    HANDLE_EXC_END
}
const std::string& HttpCommonHeaders::getContentRange() const{
    HANDLE_EXC_BEGIN
        return contentRange_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setContentType(const std::string& contentType){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    contentType_.set(contentType);
}
std::string& HttpCommonHeaders::getContentType(){
    HANDLE_EXC_BEGIN
        return contentType_.get();
    HANDLE_EXC_END
}
const std::string& HttpCommonHeaders::getContentType() const{
    HANDLE_EXC_BEGIN
        return contentType_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setContentVersion(const std::string& contentVersion){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    contentVersion_.set(contentVersion);
}
std::string& HttpCommonHeaders::getContentVersion(){
    HANDLE_EXC_BEGIN
        return contentVersion_.get();
    HANDLE_EXC_END
}
const std::string& HttpCommonHeaders::getContentVersion() const{
    HANDLE_EXC_BEGIN
        return contentVersion_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setDerivedFrom(const std::string& derivedFrom){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    derivedFrom_.set(derivedFrom);
}
std::string& HttpCommonHeaders::getDerivedFrom(){
    HANDLE_EXC_BEGIN
        return derivedFrom_.get();
    HANDLE_EXC_END
}
const std::string& HttpCommonHeaders::getDerivedFrom() const{
    HANDLE_EXC_BEGIN
        return derivedFrom_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setExpires(const std::string& expires){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    expires_.set(expires);
}
std::string& HttpCommonHeaders::getExpires(){
    HANDLE_EXC_BEGIN
        return expires_.get();
    HANDLE_EXC_END
}
const std::string& HttpCommonHeaders::getExpires() const{
    HANDLE_EXC_BEGIN
        return expires_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setLastModified(std::tm* time){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    lastModified_.set(generateDate_(time));
}
void HttpCommonHeaders::setLastModified(const std::string& lastModified){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    lastModified_.set(lastModified);
}
std::string& HttpCommonHeaders::getLastModified(){
    HANDLE_EXC_BEGIN
        return lastModified_.get();
    HANDLE_EXC_END
}
const std::string& HttpCommonHeaders::getLastModified() const{
    HANDLE_EXC_BEGIN
        return lastModified_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setLink(const std::string& link){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    link_.set(link);
}
std::string& HttpCommonHeaders::getLink(){
    HANDLE_EXC_BEGIN
        return link_.get();
    HANDLE_EXC_END
}
const std::string& HttpCommonHeaders::getLink() const{
    HANDLE_EXC_BEGIN
        return link_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setTitle(const std::string& title){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    title_.set(title);
}
std::string& HttpCommonHeaders::getTitle(){
    HANDLE_EXC_BEGIN
        return title_.get();
    HANDLE_EXC_END
}
const std::string& HttpCommonHeaders::getTitle() const{
    HANDLE_EXC_BEGIN
        return title_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::deleteData_(){
    contentDisposition_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    contentEncoding_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    contentLanguage_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    contentLength_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    contentLocation_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    contentMD5_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    contentRange_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    contentType_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    contentVersion_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    derivedFrom_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    expires_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    lastModified_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    link_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    title_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
}
void HttpCommonHeaders::copyData_(const ParserAbstractParent& o){
    const HttpCommonHeaders& other = dynamic_cast<const HttpCommonHeaders&>(o);
    
    contentDisposition_ = other.contentDisposition_;
    contentEncoding_ = other.contentEncoding_;
    contentLanguage_ = other.contentLanguage_;
    contentLength_ = other.contentLength_;
    contentLocation_ = other.contentLocation_;
    contentMD5_ = other.contentMD5_;
    contentRange_ = other.contentRange_;
    contentType_ = other.contentType_;
    contentVersion_ = other.contentVersion_;
    derivedFrom_ = other.derivedFrom_;
    expires_ = other.expires_;
    lastModified_ = other.lastModified_;
    link_ = other.link_;
    title_ = other.title_;
}
void HttpCommonHeaders::checkValidity_() const{
    
}
void HttpCommonHeaders::throwOnDone_() const{
    if (isDone_) throw ExceptionType("Common headers are done. You cannot change it anymore");
}
}
}
