#include "../../include/http_headers/common_headers.hpp"

namespace MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE{
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


namespace MAIN_NAMESPACE::HTTP_HEADERS_NAMESPACE{
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

void HttpCommonHeaders::setContentDisposition(const ContentDispositionType& contentDisposition){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::CDH);
    contentDisposition_.set(contentDisposition);
}
HttpCommonHeaders::ContentDispositionType& HttpCommonHeaders::getContentDisposition(){
    HANDLE_EXC_BEGIN
        return contentDisposition_.get();
    HANDLE_EXC_END
}
const HttpCommonHeaders::ContentDispositionType& HttpCommonHeaders::getContentDisposition() const{
    HANDLE_EXC_BEGIN
        return contentDisposition_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setContentEncoding(const ContentEncodingType& contentEncoding){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    contentEncoding_.set(contentEncoding);
}
HttpCommonHeaders::ContentEncodingType& HttpCommonHeaders::getContentEncoding(){
    HANDLE_EXC_BEGIN
        return contentEncoding_.get();
    HANDLE_EXC_END
}
const HttpCommonHeaders::ContentEncodingType& HttpCommonHeaders::getContentEncoding() const{
    HANDLE_EXC_BEGIN
        return contentEncoding_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setContentLanguage(const ContentLanguageType& contentLanguage){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    contentLanguage_.set(contentLanguage);
}
HttpCommonHeaders::ContentLanguageType& HttpCommonHeaders::getContentLanguage(){
    HANDLE_EXC_BEGIN
        return contentLanguage_.get();
    HANDLE_EXC_END
}
const HttpCommonHeaders::ContentLanguageType& HttpCommonHeaders::getContentLanguage() const{
    HANDLE_EXC_BEGIN
        return contentLanguage_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setContentLength(const ContentLengthType& contentLength){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    contentLength_.set(contentLength);
}
HttpCommonHeaders::ContentLengthType& HttpCommonHeaders::getContentLength(){
    HANDLE_EXC_BEGIN
        return contentLength_.get();
    HANDLE_EXC_END
}
const HttpCommonHeaders::ContentLengthType& HttpCommonHeaders::getContentLength() const{
    HANDLE_EXC_BEGIN
        return contentLength_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setContentLocation(const ContentLocationType& contentLocation){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    contentLocation_.set(contentLocation);
}
HttpCommonHeaders::ContentLocationType& HttpCommonHeaders::getContentLocation(){
    HANDLE_EXC_BEGIN
        return contentLocation_.get();
    HANDLE_EXC_END
}
const HttpCommonHeaders::ContentLocationType& HttpCommonHeaders::getContentLocation() const{
    HANDLE_EXC_BEGIN
        return contentLocation_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setContentMD5(const ContentMD5Type& contentMD5){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::MD5H);
    contentMD5_.set(contentMD5);
}
HttpCommonHeaders::ContentMD5Type& HttpCommonHeaders::getContentMD5(){
    HANDLE_EXC_BEGIN
        return contentMD5_.get();
    HANDLE_EXC_END
}
const HttpCommonHeaders::ContentMD5Type& HttpCommonHeaders::getContentMD5() const{
    HANDLE_EXC_BEGIN
        return contentMD5_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setContentRange(const ContentRangeType& contentRange){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    contentRange_.set(contentRange);
}
HttpCommonHeaders::ContentRangeType& HttpCommonHeaders::getContentRange(){
    HANDLE_EXC_BEGIN
        return contentRange_.get();
    HANDLE_EXC_END
}
const HttpCommonHeaders::ContentRangeType& HttpCommonHeaders::getContentRange() const{
    HANDLE_EXC_BEGIN
        return contentRange_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setContentType(const ContentType& contentType){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    contentType_.set(contentType);
}
HttpCommonHeaders::ContentType& HttpCommonHeaders::getContentType(){
    HANDLE_EXC_BEGIN
        return contentType_.get();
    HANDLE_EXC_END
}
const HttpCommonHeaders::ContentType& HttpCommonHeaders::getContentType() const{
    HANDLE_EXC_BEGIN
        return contentType_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setContentVersion(const ContentVersionType& contentVersion){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    contentVersion_.set(contentVersion);
}
HttpCommonHeaders::ContentVersionType& HttpCommonHeaders::getContentVersion(){
    HANDLE_EXC_BEGIN
        return contentVersion_.get();
    HANDLE_EXC_END
}
const HttpCommonHeaders::ContentVersionType& HttpCommonHeaders::getContentVersion() const{
    HANDLE_EXC_BEGIN
        return contentVersion_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setDerivedFrom(const DerivedFromType& derivedFrom){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    derivedFrom_.set(derivedFrom);
}
HttpCommonHeaders::DerivedFromType& HttpCommonHeaders::getDerivedFrom(){
    HANDLE_EXC_BEGIN
        return derivedFrom_.get();
    HANDLE_EXC_END
}
const HttpCommonHeaders::DerivedFromType& HttpCommonHeaders::getDerivedFrom() const{
    HANDLE_EXC_BEGIN
        return derivedFrom_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setExpires(const ExpiresType& expires){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    expires_.set(expires);
}
HttpCommonHeaders::ExpiresType& HttpCommonHeaders::getExpires(){
    HANDLE_EXC_BEGIN
        return expires_.get();
    HANDLE_EXC_END
}
const HttpCommonHeaders::ExpiresType& HttpCommonHeaders::getExpires() const{
    HANDLE_EXC_BEGIN
        return expires_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setLastModified(const LastModifiedType& lastModified){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    lastModified_.set(lastModified);
}
HttpCommonHeaders::LastModifiedType& HttpCommonHeaders::getLastModified(){
    HANDLE_EXC_BEGIN
        return lastModified_.get();
    HANDLE_EXC_END
}
const HttpCommonHeaders::LastModifiedType& HttpCommonHeaders::getLastModified() const{
    HANDLE_EXC_BEGIN
        return lastModified_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setLink(const LinkType& link){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    link_.set(link);
}
HttpCommonHeaders::LinkType& HttpCommonHeaders::getLink(){
    HANDLE_EXC_BEGIN
        return link_.get();
    HANDLE_EXC_END
}
const HttpCommonHeaders::LinkType& HttpCommonHeaders::getLink() const{
    HANDLE_EXC_BEGIN
        return link_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::setTitle(const TitleType& title){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    title_.set(title);
}
HttpCommonHeaders::TitleType& HttpCommonHeaders::getTitle(){
    HANDLE_EXC_BEGIN
        return title_.get();
    HANDLE_EXC_END
}
const HttpCommonHeaders::TitleType& HttpCommonHeaders::getTitle() const{
    HANDLE_EXC_BEGIN
        return title_.get();
    HANDLE_EXC_END
}

void HttpCommonHeaders::deleteData_(){
    contentDisposition_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentDispositionType>();
    contentEncoding_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentEncodingType>();
    contentLanguage_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentLanguageType>();
    contentLength_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentLengthType>();
    contentLocation_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentLocationType>();
    contentMD5_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentMD5Type>();
    contentRange_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentRangeType>();
    contentType_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentType>();
    contentVersion_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentVersionType>();
    derivedFrom_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<DerivedFromType>();
    expires_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ExpiresType>();
    lastModified_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<LastModifiedType>();
    link_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<LinkType>();
    title_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<TitleType>();
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