#pragma once

#include "utils.hpp"
#include "headers_abstract_parent.hpp"

namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{

class HttpGeneralHeadersException : public MAIN_NAMESPACE::UTILS_NAMESPACE::Exception {
public:
    HttpGeneralHeadersException(const char* msg);
    HttpGeneralHeadersException(const std::string& msg);

    HttpGeneralHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    HttpGeneralHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    HttpGeneralHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    HttpGeneralHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    virtual std::string output_() const;

};


class HttpGeneralHeaders : public MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent, public HttpHeadersAbstractParent{
public:
    typedef HttpGeneralHeadersException                     ExceptionType;
    typedef MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_VERSION   HttpVersionType;
    typedef std::string                                     CacheControlType;
    typedef std::string                                     ConnectionType;
    typedef std::string                                     DateType;
    typedef std::string                                     MimeVersionType;
    typedef std::string                                     PragmaType;
    typedef std::string                                     TrailerType;
    typedef std::string                                     TransferEncodingType;
    typedef std::string                                     UpgradeType;
    typedef std::string                                     ViaType;
    typedef std::string                                     WarningType;

    HttpGeneralHeaders(const StatusLineAbstractParent& statusLine);
    HttpGeneralHeaders(const HttpGeneralHeaders& other);
    ~HttpGeneralHeaders();

    HttpGeneralHeaders& operator=(const HttpGeneralHeaders& other);

    void setCacheControl(const CacheControlType& cacheControl);
    CacheControlType& getCacheControl();
    const CacheControlType& getCacheControl() const;

    void setConnection(const ConnectionType& connection);
    ConnectionType& getConnection();
    const ConnectionType& getConnection() const;

    void setDate(const DateType& date);
    DateType& getDate();
    const DateType& getDate() const;

    void setMimeVersion(const MimeVersionType& mimeVersion);
    MimeVersionType& getMimeVersion();
    const MimeVersionType& getMimeVersion() const;

    void setPragma(const PragmaType& pragma);
    PragmaType& getPragma();
    const PragmaType& getPragma() const;

    void setTrailer(const TrailerType& trailer);
    TrailerType& getTrailer();
    const TrailerType& getTrailer() const;

    void setTransferEncoding(const TransferEncodingType& transferEncoding);
    TransferEncodingType& getTransferEncoding();
    const TransferEncodingType& getTransferEncoding() const;

    void setUpgrade(const UpgradeType& upgrade);
    UpgradeType& getUpgrade();
    const UpgradeType& getUpgrade() const;

    void setVia(const ViaType& via);
    ViaType& getVia();
    const ViaType& getVia() const;

    void setWarning(const WarningType& warning);
    WarningType& getWarning();
    const WarningType& getWarning() const;

private:
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<CacheControlType> cacheControl_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ConnectionType> connection_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<DateType> date_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<MimeVersionType> mimeVersion_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<PragmaType> pragma_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<TrailerType> trailer_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<TransferEncodingType> transferEncoding_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<UpgradeType> upgrade_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ViaType> via_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<WarningType> warning_;

    void deleteData_();
    void copyData_(const ParserAbstractParent& o);
    void checkValidity_() const;
    void throwOnDone_() const;

};

}
}
