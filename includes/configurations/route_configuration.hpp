#pragma once

#include "utils.hpp"

namespace MAIN_NAMESPACE {
namespace CONFIG_NAMESPACE{

class RouteException : public MAIN_NAMESPACE::UTILS_NAMESPACE::Exception {
public:
    RouteException(const char* msg);
    RouteException(const std::string& msg);

    RouteException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_);
    RouteException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_);

    RouteException(const char* msg, const std::string& _file_, const std::string& _function_, int _line_, int code);
    RouteException(const std::string& msg, const std::string& _file_, const std::string& _function_, int _line_, int code);

protected:
    std::string output_() const;

};

// Contains information about server's route.
// Any getter may throw RouteException if it's value is not set.
// Use methods [isDone()] to check if the route is finished or not.
// Method [done()] marks the route as finished. May throw an exception.
class RouteConfiguration : public MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent{
public:
    typedef int                                                         MethodType;
    typedef MAIN_NAMESPACE::UTILS_NAMESPACE::Container<MethodType>      MethodsContainerType;
    typedef RouteException                                              ExceptionType;

    explicit RouteConfiguration();
    explicit RouteConfiguration(const RouteConfiguration& other);
    ~RouteConfiguration();

    RouteConfiguration& operator=(const RouteConfiguration& other);

    void setMethods(const MethodsContainerType& methods);
    MethodsContainerType& getMethods();
    const MethodsContainerType& getMethods() const;
    void setMethod(const MethodType& method, size_t position);
    MethodType& getMethod(size_t position);
    const MethodType& getMethod(size_t position) const;
    void addMethod(const MethodType& method);
    size_t getMethodsCount() const;

    void setRedirection(const std::string& redirection);
    std::string& getRedirection();
    const std::string& getRedirection() const;

    void setDirectory(const std::string& directory);
    std::string& getDirectory();
    const std::string& getDirectory() const;

    void setDirectoryListening(bool directoryListening);
    bool getDirectoryListening() const;

    void setDefaultIfDirectoryResponse(const std::string& default_if_directory_response_path);
    std::string& getDefaultIfDirectoryResponse();
    const std::string& getDefaultIfDirectoryResponse() const;

    void setCgiScriptPath(const std::string& cgi_script_path);
    std::string& getCgiScriptPath();
    const std::string& getCgiScriptPath() const;

    void setCgiBinPath(const std::string& cgi_bin_path);
    std::string& getCgiBinPath();
    const std::string& getCgiBinPath() const;

    void setSaveFiles(bool saveFiles);
    bool getSaveFiles() const;

    void setSaveTo(const std::string& saveTo);
    std::string& getSaveTo();
    const std::string& getSaveTo() const;

private:
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<MethodsContainerType> methods_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> redirection_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> directory_;
    bool directory_listening_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> default_if_directory_response_path_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> cgi_script_path_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> cgi_bin_path_;
    bool saveFiles_;
    MAIN_NAMESPACE::UTILS_NAMESPACE::Wrapper<std::string> saveTo_;

    void deleteData_();
    void copyData_(const MAIN_NAMESPACE::UTILS_NAMESPACE::ParserAbstractParent& o);
    void checkValidity_() const;
    void throwOnDone_() const;

};

}
}
