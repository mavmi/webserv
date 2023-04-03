#include "../../includes/http_headers/general_headers.hpp"

namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{
HttpGeneralHeadersException::HttpGeneralHeadersException(const char* msg) : Exception(msg){}
HttpGeneralHeadersException::HttpGeneralHeadersException(const std::string& msg) : Exception(msg){}
HttpGeneralHeadersException::HttpGeneralHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpGeneralHeadersException::HttpGeneralHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_) 
    : Exception(msg, _file_, _function_, _line_) {}
HttpGeneralHeadersException::HttpGeneralHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
HttpGeneralHeadersException::HttpGeneralHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code)
    : Exception(msg, _file_, _function_, _line_, code) {}
std::string HttpGeneralHeadersException::output_() const {
    return "HTTP_GENERAL_HEADERS_EXCEPTION: " + msg_;
}
}
}


namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{
HttpGeneralHeaders::HttpGeneralHeaders(const StatusLineAbstractParent& statusLine)
    : HttpHeadersAbstractParent(statusLine) {
    
}
HttpGeneralHeaders::HttpGeneralHeaders(const HttpGeneralHeaders& other)
    : ParserAbstractParent(other), HttpHeadersAbstractParent(other.statusLine_) {
    copyData_(other);
}
HttpGeneralHeaders::~HttpGeneralHeaders(){
    deleteData_();
}
 
HttpGeneralHeaders& HttpGeneralHeaders::operator=(const HttpGeneralHeaders& other){
    deleteData_();
    copyData_(other);
    return *this;
}

void HttpGeneralHeaders::setCacheControl(const std::string& cacheControl){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    cacheControl_.set(cacheControl);
}
std::string& HttpGeneralHeaders::getCacheControl(){
    HANDLE_EXC_BEGIN
        return cacheControl_.get();
    HANDLE_EXC_END
}
const std::string& HttpGeneralHeaders::getCacheControl() const{
    HANDLE_EXC_BEGIN
        return cacheControl_.get();
    HANDLE_EXC_END
}

void HttpGeneralHeaders::setConnection(const std::string& connection){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    connection_.set(connection);
}
std::string& HttpGeneralHeaders::getConnection(){
    HANDLE_EXC_BEGIN
        return connection_.get();
    HANDLE_EXC_END
}
const std::string& HttpGeneralHeaders::getConnection() const{
    HANDLE_EXC_BEGIN
        return connection_.get();
    HANDLE_EXC_END
}

void HttpGeneralHeaders::setDate(){
    throwOnDone_();
    // checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);

    std::time_t t = std::time(NULL);
    date_.set(generateDate_(std::localtime(&t)));
}
void HttpGeneralHeaders::setDate(const std::string& date){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    date_.set(date);
}
std::string& HttpGeneralHeaders::getDate(){
    HANDLE_EXC_BEGIN
        return date_.get();
    HANDLE_EXC_END
}
const std::string& HttpGeneralHeaders::getDate() const{
    HANDLE_EXC_BEGIN
        return date_.get();
    HANDLE_EXC_END
}

void HttpGeneralHeaders::setMimeVersion(const std::string& mimeVersion){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::MIME);
    mimeVersion_.set(mimeVersion);
}
std::string& HttpGeneralHeaders::getMimeVersion(){
    HANDLE_EXC_BEGIN
        return mimeVersion_.get();
    HANDLE_EXC_END
}
const std::string& HttpGeneralHeaders::getMimeVersion() const{
    HANDLE_EXC_BEGIN
        return mimeVersion_.get();
    HANDLE_EXC_END
}

void HttpGeneralHeaders::setPragma(const std::string& pragma){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    pragma_.set(pragma);
}
std::string& HttpGeneralHeaders::getPragma(){
    HANDLE_EXC_BEGIN
        return pragma_.get();
    HANDLE_EXC_END
}
const std::string& HttpGeneralHeaders::getPragma() const{
    HANDLE_EXC_BEGIN
        return pragma_.get();
    HANDLE_EXC_END
}

void HttpGeneralHeaders::setTrailer(const std::string& trailer){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1v2);
    trailer_.set(trailer);
}
std::string& HttpGeneralHeaders::getTrailer(){
    HANDLE_EXC_BEGIN
        return trailer_.get();
    HANDLE_EXC_END
}
const std::string& HttpGeneralHeaders::getTrailer() const{
    HANDLE_EXC_BEGIN
        return trailer_.get();
    HANDLE_EXC_END
}

void HttpGeneralHeaders::setTransferEncoding(const std::string& transferEncoding){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    transferEncoding_.set(transferEncoding);
}
std::string& HttpGeneralHeaders::getTransferEncoding(){
    HANDLE_EXC_BEGIN
        return transferEncoding_.get();
    HANDLE_EXC_END
}
const std::string& HttpGeneralHeaders::getTransferEncoding() const{
    HANDLE_EXC_BEGIN
        return transferEncoding_.get();
    HANDLE_EXC_END
}

void HttpGeneralHeaders::setUpgrade(const std::string& upgrade){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    upgrade_.set(upgrade);
}
std::string& HttpGeneralHeaders::getUpgrade(){
    HANDLE_EXC_BEGIN
        return upgrade_.get();
    HANDLE_EXC_END
}
const std::string& HttpGeneralHeaders::getUpgrade() const{
    HANDLE_EXC_BEGIN
        return upgrade_.get();
    HANDLE_EXC_END
}

void HttpGeneralHeaders::setVia(const std::string& via){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    via_.set(via);
}
std::string& HttpGeneralHeaders::getVia(){
    HANDLE_EXC_BEGIN
        return via_.get();
    HANDLE_EXC_END
}
const std::string& HttpGeneralHeaders::getVia() const{
    HANDLE_EXC_BEGIN
        return via_.get();
    HANDLE_EXC_END
}

void HttpGeneralHeaders::setWarning(const std::string& warning){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    warning_.set(warning);
}
std::string& HttpGeneralHeaders::getWarning(){
    HANDLE_EXC_BEGIN
        return warning_.get();
    HANDLE_EXC_END
}
const std::string& HttpGeneralHeaders::getWarning() const{
    HANDLE_EXC_BEGIN
        return warning_.get();
    HANDLE_EXC_END
}

void HttpGeneralHeaders::deleteData_(){
    cacheControl_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    connection_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    date_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    mimeVersion_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    pragma_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    trailer_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    transferEncoding_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    upgrade_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    via_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
    warning_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string>();
}
void HttpGeneralHeaders::copyData_(const ParserAbstractParent& o){
    const HttpGeneralHeaders& other = dynamic_cast<const HttpGeneralHeaders&>(o);

    cacheControl_ = other.cacheControl_;
    connection_ = other.connection_;
    date_ = other.date_;
    mimeVersion_ = other.mimeVersion_;
    pragma_ = other.pragma_;
    trailer_ = other.trailer_;
    transferEncoding_ = other.transferEncoding_;
    upgrade_ = other.upgrade_;
    via_ = other.via_;
    warning_ = other.warning_;
}
void HttpGeneralHeaders::checkValidity_() const{

}
void HttpGeneralHeaders::throwOnDone_() const{
    if (isDone_) throw ExceptionType("General headers are done. You cannot change it anymore.");
}
}
}
