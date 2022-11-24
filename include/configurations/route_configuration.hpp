#pragma once

#include "utils.hpp"
#include "wrapper.hpp"
#include "container.hpp"
#include "exceptions.hpp"

namespace configuration {

// Contains information about server's route.
// Any getter may throw RouteException if it's value is not set.
// Use methods [isDone()] to check if the route is finished or not.
// Method [done()] marks the route as finished. May throw an exception.
class RouteConfiguration{
friend Configuration;
friend ServerConfiguration;
friend Container<RouteConfiguration>;
public:
    typedef size_t                      SizeType;
    typedef int                         MethodType;
    typedef Container<MethodType>       MethodsContainerType;
    typedef std::string                 PathType;
    typedef RouteException              ExceptionType;

    ~RouteConfiguration();

    void setMethods(const MethodsContainerType& methods);
    MethodsContainerType& getMethods();
    const MethodsContainerType& getMethods() const;
    void setMethod(const MethodType& method, SizeType position);
    MethodType& getMethod(SizeType position);
    const MethodType& getMethod(SizeType position) const;
    void addMethod(const MethodType& method);
    SizeType getMethodsCount() const;

    void setRedirection(const PathType& redirection);
    PathType& getRedirection();
    const PathType& getRedirection() const;

    void setDirectory(const PathType& directory);
    PathType& getDirectory();
    const PathType& getDirectory() const;

    void setDirectoryListening(bool directoryListening);
    bool getDirectoryListening() const;

    void setDefaultIfDirectoryResponse(const PathType& default_if_directory_response_path);
    PathType& getDefaultIfDirectoryResponse();
    const PathType& getDefaultIfDirectoryResponse() const;

    void setCgiScriptPath(const PathType& cgi_script_path);
    PathType& getCgiScriptPath();
    const PathType& getCgiScriptPath() const;

    void setCgiBinPath(const PathType& cgi_bin_path);
    PathType& getCgiBinPath();
    const PathType& getCgiBinPath() const;

    void setSaveFiles(bool saveFiles);
    bool getSaveFiles() const;

    void setSaveTo(const PathType& saveTo);
    PathType& getSaveTo();
    const PathType& getSaveTo() const;

    bool isDone() const;
    void done();

private:
    bool isDone_;
    Wrapper<MethodsContainerType> methods_;
    Wrapper<PathType> redirection_;
    Wrapper<PathType> directory_;
    bool directory_listening_;
    Wrapper<PathType> default_if_directory_response_path_;
    Wrapper<PathType> cgi_script_path_;
    Wrapper<PathType> cgi_bin_path_;
    bool saveFiles_;
    Wrapper<PathType> saveTo_;

    explicit RouteConfiguration();
    explicit RouteConfiguration(const RouteConfiguration& other);

    RouteConfiguration& operator=(const RouteConfiguration& other);
    static void* operator new(size_t size);
    static void* operator new(size_t size, const RouteConfiguration& other);
    static void* operator new[](size_t size);
    static void operator delete(void* ptr);
    static void operator delete[](void* ptr);

    void deleteData_();
    void copyData_(const RouteConfiguration& other);
    void checkValidity_() const;
    void throwOnDone() const;

};

}
