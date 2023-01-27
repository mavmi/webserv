#include "../../include/http_headers/general_headers.hpp"

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

void HttpGeneralHeaders::setCacheControl(const CacheControlType& cacheControl){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    cacheControl_.set(cacheControl);
}
HttpGeneralHeaders::CacheControlType& HttpGeneralHeaders::getCacheControl(){
    HANDLE_EXC_BEGIN
        return cacheControl_.get();
    HANDLE_EXC_END
}
const HttpGeneralHeaders::CacheControlType& HttpGeneralHeaders::getCacheControl() const{
    HANDLE_EXC_BEGIN
        return cacheControl_.get();
    HANDLE_EXC_END
}

void HttpGeneralHeaders::setConnection(const ConnectionType& connection){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    connection_.set(connection);
}
HttpGeneralHeaders::ConnectionType& HttpGeneralHeaders::getConnection(){
    HANDLE_EXC_BEGIN
        return connection_.get();
    HANDLE_EXC_END
}
const HttpGeneralHeaders::ConnectionType& HttpGeneralHeaders::getConnection() const{
    HANDLE_EXC_BEGIN
        return connection_.get();
    HANDLE_EXC_END
}

void HttpGeneralHeaders::setDate(const DateType& date){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    date_.set(date);
}
HttpGeneralHeaders::DateType& HttpGeneralHeaders::getDate(){
    HANDLE_EXC_BEGIN
        return date_.get();
    HANDLE_EXC_END
}
const HttpGeneralHeaders::DateType& HttpGeneralHeaders::getDate() const{
    HANDLE_EXC_BEGIN
        return date_.get();
    HANDLE_EXC_END
}

void HttpGeneralHeaders::setMimeVersion(const MimeVersionType& mimeVersion){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::MIME);
    mimeVersion_.set(mimeVersion);
}
HttpGeneralHeaders::MimeVersionType& HttpGeneralHeaders::getMimeVersion(){
    HANDLE_EXC_BEGIN
        return mimeVersion_.get();
    HANDLE_EXC_END
}
const HttpGeneralHeaders::MimeVersionType& HttpGeneralHeaders::getMimeVersion() const{
    HANDLE_EXC_BEGIN
        return mimeVersion_.get();
    HANDLE_EXC_END
}

void HttpGeneralHeaders::setPragma(const PragmaType& pragma){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_0);
    pragma_.set(pragma);
}
HttpGeneralHeaders::PragmaType& HttpGeneralHeaders::getPragma(){
    HANDLE_EXC_BEGIN
        return pragma_.get();
    HANDLE_EXC_END
}
const HttpGeneralHeaders::PragmaType& HttpGeneralHeaders::getPragma() const{
    HANDLE_EXC_BEGIN
        return pragma_.get();
    HANDLE_EXC_END
}

void HttpGeneralHeaders::setTrailer(const TrailerType& trailer){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1v2);
    trailer_.set(trailer);
}
HttpGeneralHeaders::TrailerType& HttpGeneralHeaders::getTrailer(){
    HANDLE_EXC_BEGIN
        return trailer_.get();
    HANDLE_EXC_END
}
const HttpGeneralHeaders::TrailerType& HttpGeneralHeaders::getTrailer() const{
    HANDLE_EXC_BEGIN
        return trailer_.get();
    HANDLE_EXC_END
}

void HttpGeneralHeaders::setTransferEncoding(const TransferEncodingType& transferEncoding){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    transferEncoding_.set(transferEncoding);
}
HttpGeneralHeaders::TransferEncodingType& HttpGeneralHeaders::getTransferEncoding(){
    HANDLE_EXC_BEGIN
        return transferEncoding_.get();
    HANDLE_EXC_END
}
const HttpGeneralHeaders::TransferEncodingType& HttpGeneralHeaders::getTransferEncoding() const{
    HANDLE_EXC_BEGIN
        return transferEncoding_.get();
    HANDLE_EXC_END
}

void HttpGeneralHeaders::setUpgrade(const UpgradeType& upgrade){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    upgrade_.set(upgrade);
}
HttpGeneralHeaders::UpgradeType& HttpGeneralHeaders::getUpgrade(){
    HANDLE_EXC_BEGIN
        return upgrade_.get();
    HANDLE_EXC_END
}
const HttpGeneralHeaders::UpgradeType& HttpGeneralHeaders::getUpgrade() const{
    HANDLE_EXC_BEGIN
        return upgrade_.get();
    HANDLE_EXC_END
}

void HttpGeneralHeaders::setVia(const ViaType& via){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    via_.set(via);
}
HttpGeneralHeaders::ViaType& HttpGeneralHeaders::getVia(){
    HANDLE_EXC_BEGIN
        return via_.get();
    HANDLE_EXC_END
}
const HttpGeneralHeaders::ViaType& HttpGeneralHeaders::getVia() const{
    HANDLE_EXC_BEGIN
        return via_.get();
    HANDLE_EXC_END
}

void HttpGeneralHeaders::setWarning(const WarningType& warning){
    throwOnDone_();
    checkVersion_(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_1_1);
    warning_.set(warning);
}
HttpGeneralHeaders::WarningType& HttpGeneralHeaders::getWarning(){
    HANDLE_EXC_BEGIN
        return warning_.get();
    HANDLE_EXC_END
}
const HttpGeneralHeaders::WarningType& HttpGeneralHeaders::getWarning() const{
    HANDLE_EXC_BEGIN
        return warning_.get();
    HANDLE_EXC_END
}

void HttpGeneralHeaders::deleteData_(){
    cacheControl_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<CacheControlType>();
    connection_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ConnectionType>();
    date_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<DateType>();
    mimeVersion_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<MimeVersionType>();
    pragma_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<PragmaType>();
    trailer_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<TrailerType>();
    transferEncoding_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<TransferEncodingType>();
    upgrade_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<UpgradeType>();
    via_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ViaType>();
    warning_ = MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<WarningType>();
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
