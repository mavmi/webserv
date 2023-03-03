#pragma once

#include "utils.hpp"
#include "headers_abstract_parent.hpp"

namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{

class HttpCommonHeadersException : public MAIN_NAMESPACE::UTILS_NAMESPACE::Exception {
public:
    HttpCommonHeadersException(const char* msg);
    HttpCommonHeadersException(const std::string& msg);

    HttpCommonHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    HttpCommonHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    HttpCommonHeadersException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    HttpCommonHeadersException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    virtual std::string output_() const;

};


class HttpCommonHeaders : public MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent, public HttpHeadersAbstractParent{
public:
    typedef HttpCommonHeadersException      ExceptionType;
    typedef std::string                     ContentDispositionType;
    typedef std::string                     ContentEncodingType;
    typedef std::string                     ContentLanguageType;
    typedef std::string                     ContentLengthType;
    typedef std::string                     ContentLocationType;
    typedef std::string                     ContentMD5Type;
    typedef std::string                     ContentRangeType;
    typedef std::string                     ContentType;
    typedef std::string                     ContentVersionType;
    typedef std::string                     DerivedFromType;
    typedef std::string                     ExpiresType;
    typedef DateType                        LastModifiedType;
    typedef std::string                     LinkType;
    typedef std::string                     TitleType;

    HttpCommonHeaders(const StatusLineAbstractParent& statusLine);
    HttpCommonHeaders(const HttpCommonHeaders& other);
    ~HttpCommonHeaders();

    HttpCommonHeaders& operator=(const HttpCommonHeaders& other);

    void setContentDisposition(const ContentDispositionType& contentDisposition);
    ContentDispositionType& getContentDisposition();
    const ContentDispositionType& getContentDisposition() const;

    void setContentEncoding(const ContentEncodingType& contentEncoding);
    ContentEncodingType& getContentEncoding();
    const ContentEncodingType& getContentEncoding() const;

    void setContentLanguage(const ContentLanguageType& contentLanguage);
    ContentLanguageType& getContentLanguage();
    const ContentLanguageType& getContentLanguage() const;

    void setContentLength(const ContentLengthType& contentLength);
    ContentLengthType& getContentLength();
    const ContentLengthType& getContentLength() const;

    void setContentLocation(const ContentLocationType& contentLocation);
    ContentLocationType& getContentLocation();
    const ContentLocationType& getContentLocation() const;

    void setContentMD5(const ContentMD5Type& contentMD5);
    ContentMD5Type& getContentMD5();
    const ContentMD5Type& getContentMD5() const;

    void setContentRange(const ContentRangeType& contentRange);
    ContentRangeType& getContentRange();
    const ContentRangeType& getContentRange() const;

    void setContentType(const ContentType& contentType);
    ContentType& getContentType();
    const ContentType& getContentType() const;

    void setContentVersion(const ContentVersionType& contentVersion);
    ContentVersionType& getContentVersion();
    const ContentVersionType& getContentVersion() const;

    void setDerivedFrom(const DerivedFromType& derivedFrom);
    DerivedFromType& getDerivedFrom();
    const DerivedFromType& getDerivedFrom() const;

    void setExpires(const ExpiresType& expires);
    ExpiresType& getExpires();
    const ExpiresType& getExpires() const;

    void setLastModified(std::tm* time);
    void setLastModified(const LastModifiedType& lastModified);
    LastModifiedType& getLastModified();
    const LastModifiedType& getLastModified() const;

    void setLink(const LinkType& link);
    LinkType& getLink();
    const LinkType& getLink() const;

    void setTitle(const TitleType& title);
    TitleType& getTitle();
    const TitleType& getTitle() const;

private:
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentDispositionType> contentDisposition_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentEncodingType> contentEncoding_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentLanguageType> contentLanguage_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentLengthType> contentLength_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentLocationType> contentLocation_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentMD5Type> contentMD5_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentRangeType> contentRange_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentType> contentType_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ContentVersionType> contentVersion_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<DerivedFromType> derivedFrom_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<ExpiresType> expires_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<LastModifiedType> lastModified_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<LinkType> link_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<TitleType> title_;

    void deleteData_();
    void copyData_(const ParserAbstractParent& o);
    void checkValidity_() const;
    void throwOnDone_() const;

};

}
}
