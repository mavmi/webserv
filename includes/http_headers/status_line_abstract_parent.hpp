#pragma once

#include "utils.hpp"

namespace MAIN_NAMESPACE{
namespace HTTP_HEADERS_NAMESPACE{
class StatusLineAbstractParentException : public MAIN_NAMESPACE::UTILS_NAMESPACE::Exception {
public:
    StatusLineAbstractParentException(const char* msg);
    StatusLineAbstractParentException(const std::string& msg);

    StatusLineAbstractParentException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    StatusLineAbstractParentException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    StatusLineAbstractParentException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    StatusLineAbstractParentException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    virtual std::string output_() const;

};


class StatusLineAbstractParent : public MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent{
public:
    typedef StatusLineAbstractParentException               ExceptionType;

    void setHttpVersion(MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_VERSION httpVersion);
    MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_VERSION& getHttpVersion();
    const MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_VERSION& getHttpVersion() const;

protected:
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<MAIN_NAMESPACE::UTILS_NAMESPACE::HTTP_VERSION> httpVersion_;

    StatusLineAbstractParent();
    StatusLineAbstractParent(const StatusLineAbstractParent& other);
    ~StatusLineAbstractParent();

    StatusLineAbstractParent& operator=(const StatusLineAbstractParent& other);

    void deleteData_();
    void copyData_(const MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent& other);
    void checkValidity_() const;
    void throwOnDone_() const;

};
}
}
