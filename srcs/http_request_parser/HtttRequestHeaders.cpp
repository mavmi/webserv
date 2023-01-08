#include "../../include/http_request_parser/HtttRequestHeaders.hpp"

namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{
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


namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{
HttpRequestHeaders::HttpRequestHeaders(const HttpRequestStatusLine& statusLine)
    : HttpHeadersAbstractParent(statusLine) {

}
HttpRequestHeaders::HttpRequestHeaders(const HttpRequestHeaders& other)
    : ParserAbstractParent(other), HttpHeadersAbstractParent(other.statusLine_) {
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
    checkVersion_(HttpRequestStatusLine::HTTP_1_0);
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
    checkVersion_(HttpRequestStatusLine::HTTP_1_0);
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
    checkVersion_(HttpRequestStatusLine::HTTP_1_0);
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
    checkVersion_(HttpRequestStatusLine::HTTP_1_0);
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
    checkVersion_(HttpRequestStatusLine::HTTP_AUTH);
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

void HttpRequestHeaders::setContentDisposition(const ContentDispositionType& contentDisposition){
    throwOnDone_();
    checkVersion_(HttpRequestStatusLine::CDH);
    contentDisposition_.set(contentDisposition);
}
HttpRequestHeaders::ContentDispositionType& HttpRequestHeaders::getContentDisposition(){
    HANDLE_EXC_BEGIN
        return contentDisposition_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::ContentDispositionType& HttpRequestHeaders::getContentDisposition() const{
    HANDLE_EXC_BEGIN
        return contentDisposition_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setContentEncoding(const ContentEncodingType& contentEncoding){
    throwOnDone_();
    checkVersion_(HttpRequestStatusLine::HTTP_1_0);
    contentEncoding_.set(contentEncoding);
}
HttpRequestHeaders::ContentEncodingType& HttpRequestHeaders::getContentEncoding(){
    HANDLE_EXC_BEGIN
        return contentEncoding_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::ContentEncodingType& HttpRequestHeaders::getContentEncoding() const{
    HANDLE_EXC_BEGIN
        return contentEncoding_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setContentLanguage(const ContentLanguageType& contentLanguage){
    throwOnDone_();
    checkVersion_(HttpRequestStatusLine::HTTP_1_0);
    contentLanguage_.set(contentLanguage);
}
HttpRequestHeaders::ContentLanguageType& HttpRequestHeaders::getContentLanguage(){
    HANDLE_EXC_BEGIN
        return contentLanguage_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::ContentLanguageType& HttpRequestHeaders::getContentLanguage() const{
    HANDLE_EXC_BEGIN
        return contentLanguage_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setContentLength(const ContentLengthType& contentLength){
    throwOnDone_();
    checkVersion_(HttpRequestStatusLine::HTTP_1_0);
    contentLength_.set(contentLength);
}
HttpRequestHeaders::ContentLengthType& HttpRequestHeaders::getContentLength(){
    HANDLE_EXC_BEGIN
        return contentLength_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::ContentLengthType& HttpRequestHeaders::getContentLength() const{
    HANDLE_EXC_BEGIN
        return contentLength_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setContentLocation(const ContentLocationType& contentLocation){
    throwOnDone_();
    checkVersion_(HttpRequestStatusLine::HTTP_1_1);
    contentLocation_.set(contentLocation);
}
HttpRequestHeaders::ContentLocationType& HttpRequestHeaders::getContentLocation(){
    HANDLE_EXC_BEGIN
        return contentLocation_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::ContentLocationType& HttpRequestHeaders::getContentLocation() const{
    HANDLE_EXC_BEGIN
        return contentLocation_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setContentMD5(const ContentMD5Type& contentMD5){
    throwOnDone_();
    checkVersion_(HttpRequestStatusLine::MD5H);
    contentMD5_.set(contentMD5);
}
HttpRequestHeaders::ContentMD5Type& HttpRequestHeaders::getContentMD5(){
    HANDLE_EXC_BEGIN
        return contentMD5_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::ContentMD5Type& HttpRequestHeaders::getContentMD5() const{
    HANDLE_EXC_BEGIN
        return contentMD5_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setContentRange(const ContentRangeType& contentRange){
    throwOnDone_();
    checkVersion_(HttpRequestStatusLine::HTTP_1_1);
    contentRange_.set(contentRange);
}
HttpRequestHeaders::ContentRangeType& HttpRequestHeaders::getContentRange(){
    HANDLE_EXC_BEGIN
        return contentRange_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::ContentRangeType& HttpRequestHeaders::getContentRange() const{
    HANDLE_EXC_BEGIN
        return contentRange_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setContentType(const ContentType& contentType){
    throwOnDone_();
    checkVersion_(HttpRequestStatusLine::HTTP_1_0);
    contentType_.set(contentType);
}
HttpRequestHeaders::ContentType& HttpRequestHeaders::getContentType(){
    HANDLE_EXC_BEGIN
        return contentType_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::ContentType& HttpRequestHeaders::getContentType() const{
    HANDLE_EXC_BEGIN
        return contentType_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setContentVersion(const ContentVersionType& contentVersion){
    throwOnDone_();
    checkVersion_(HttpRequestStatusLine::HTTP_1_1);
    contentVersion_.set(contentVersion);
}
HttpRequestHeaders::ContentVersionType& HttpRequestHeaders::getContentVersion(){
    HANDLE_EXC_BEGIN
        return contentVersion_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::ContentVersionType& HttpRequestHeaders::getContentVersion() const{
    HANDLE_EXC_BEGIN
        return contentVersion_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setDerivedFrom(const DerivedFromType& derivedFrom){
    throwOnDone_();
    checkVersion_(HttpRequestStatusLine::HTTP_1_1);
    derivedFrom_.set(derivedFrom);
}
HttpRequestHeaders::DerivedFromType& HttpRequestHeaders::getDerivedFrom(){
    HANDLE_EXC_BEGIN
        return derivedFrom_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::DerivedFromType& HttpRequestHeaders::getDerivedFrom() const{
    HANDLE_EXC_BEGIN
        return derivedFrom_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setExpect(const ExpectType& expect){
    throwOnDone_();
    checkVersion_(HttpRequestStatusLine::HTTP_1_1v2);
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

void HttpRequestHeaders::setExpires(const ExpiresType& expires){
    throwOnDone_();
    checkVersion_(HttpRequestStatusLine::HTTP_1_0);
    expires_.set(expires);
}
HttpRequestHeaders::ExpiresType& HttpRequestHeaders::getExpires(){
    HANDLE_EXC_BEGIN
        return expires_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::ExpiresType& HttpRequestHeaders::getExpires() const{
    HANDLE_EXC_BEGIN
        return expires_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setFrom(const FromType& from){
    throwOnDone_();
    checkVersion_(HttpRequestStatusLine::HTTP_1_1);
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
    checkVersion_(HttpRequestStatusLine::HTTP_1_1);
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
    checkVersion_(HttpRequestStatusLine::HTTP_1_1);
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
    checkVersion_(HttpRequestStatusLine::HTTP_1_0);
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
    checkVersion_(HttpRequestStatusLine::HTTP_1_1);
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
    checkVersion_(HttpRequestStatusLine::HTTP_1_1);
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
    checkVersion_(HttpRequestStatusLine::HTTP_1_1);
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

void HttpRequestHeaders::setLastModified(const LastModifiedType& lastModified){
    throwOnDone_();
    checkVersion_(HttpRequestStatusLine::HTTP_1_0);
    lastModified_.set(lastModified);
}
HttpRequestHeaders::LastModifiedType& HttpRequestHeaders::getLastModified(){
    HANDLE_EXC_BEGIN
        return lastModified_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::LastModifiedType& HttpRequestHeaders::getLastModified() const{
    HANDLE_EXC_BEGIN
        return lastModified_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setLink(const LinkType& link){
    throwOnDone_();
    checkVersion_(HttpRequestStatusLine::HTTP_1_0);
    link_.set(link);
}
HttpRequestHeaders::LinkType& HttpRequestHeaders::getLink(){
    HANDLE_EXC_BEGIN
        return link_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::LinkType& HttpRequestHeaders::getLink() const{
    HANDLE_EXC_BEGIN
        return link_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setMaxForwards(const MaxForwardsType& maxForwards){
    throwOnDone_();
    checkVersion_(HttpRequestStatusLine::HTTP_1_1);
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
    checkVersion_(HttpRequestStatusLine::HTTP_AUTH);
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
    checkVersion_(HttpRequestStatusLine::HTTP_1_1);
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
    checkVersion_(HttpRequestStatusLine::HTTP_1_0);
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

void HttpRequestHeaders::setTitle(const TitleType& title){
    throwOnDone_();
    checkVersion_(HttpRequestStatusLine::HTTP_1_0);
    title_.set(title);
}
HttpRequestHeaders::TitleType& HttpRequestHeaders::getTitle(){
    HANDLE_EXC_BEGIN
        return title_.get();
    HANDLE_EXC_END
}
const HttpRequestHeaders::TitleType& HttpRequestHeaders::getTitle() const{
    HANDLE_EXC_BEGIN
        return title_.get();
    HANDLE_EXC_END
}

void HttpRequestHeaders::setTE(const TEType& TE){
    throwOnDone_();
    checkVersion_(HttpRequestStatusLine::HTTP_1_1v2);
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
    checkVersion_(HttpRequestStatusLine::HTTP_1_0);
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
    expect_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ExpectType>();
    expires_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ExpiresType>();
    from_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<FromType>();
    host_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<HostType>();
    ifMatch_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<IfMatchType>();
    ifModifiedSince_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<IfModifiedSinceType>();
    ifNoneMatch_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<IfNoneMatchType>();
    ifRange_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<IfRangeType>();
    ifUnmodifiedSince_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<IfUnmodifiedSinceType>();
    lastModified_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<LastModifiedType>();
    link_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<LinkType>();
    maxForwards_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<MaxForwardsType>();
    proxyAuthorization_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ProxyAuthorizationType>();
    range_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<RangeType>();
    referer_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<RefererType>();
    title_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<TitleType>();
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
    expect_ = other.expect_;
    expires_ = other.expires_;
    from_ = other.from_;
    host_ = other.host_;
    ifMatch_ = other.ifMatch_;
    ifModifiedSince_ = other.ifModifiedSince_;
    ifNoneMatch_ = other.ifNoneMatch_;
    ifRange_ = other.ifRange_;
    ifUnmodifiedSince_ = other.ifUnmodifiedSince_;
    lastModified_ = other.lastModified_;
    link_ = other.link_;
    maxForwards_ = other.maxForwards_;
    proxyAuthorization_ = other.proxyAuthorization_;
    range_ = other.range_;
    referer_ = other.referer_;
    title_ = other.title_;
    TE_ = other.TE_;
    userAgent_ = other.userAgent_;
}
void HttpRequestHeaders::checkValidity_() const{
    
}
void HttpRequestHeaders::throwOnDone_() const{
    if (isDone_) throw ExceptionType("Request headers are done. You cannot change it anymore");
}
}