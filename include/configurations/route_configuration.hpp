#pragma once

#include "utils.hpp"
#include "exceptions.hpp"

// Contains information about server's route.
// Any getter may throw RouteException if it's value is not set.
// Use methods [isDone()] to check if the route is finished or not.
// Method [done()] marks the route as finished.
class RouteConfiguration{
public:
    typedef size_t                      SIZE_TYPE;
    typedef int                         METHOD_TYPE;
    typedef std::vector<METHOD_TYPE>    METHODS_CONTAINER_TYPE;
    typedef std::string                 PATH_TYPE;

    RouteConfiguration();
    RouteConfiguration(const RouteConfiguration& other);
    ~RouteConfiguration();

    RouteConfiguration& operator=(const RouteConfiguration& other);

    void setMethods(const METHODS_CONTAINER_TYPE& methods);
    METHODS_CONTAINER_TYPE& getMethods() const;
    void setMethod(const METHOD_TYPE& method, SIZE_TYPE position);
    METHOD_TYPE& getMethod(SIZE_TYPE position) const;
    void addMethod(const METHOD_TYPE& method);
    SIZE_TYPE getMethodsCount() const;

    void setRedirection(const PATH_TYPE& redirection);
    PATH_TYPE& getRedirection() const;

    void setDirectory(const PATH_TYPE& directory);
    PATH_TYPE& getDirectory() const;

    void setDirectoryListening(bool directoryListening);
    bool getDirectoryListening() const;

    void setDefaultIfDirectoryResponse(const PATH_TYPE& default_if_directory_response_path);
    PATH_TYPE& getDefaultIfDirectoryResponse() const;

    void setCgiScriptPath(const PATH_TYPE& cgi_script_path);
    PATH_TYPE& getCgiScriptPath() const;

    void setCgiBinPath(const PATH_TYPE& cgi_bin_path);
    PATH_TYPE& getCgiBinPath() const;

    bool isDone() const;
    void done();

private:
    bool isDone_;
    METHODS_CONTAINER_TYPE* methods_;
    PATH_TYPE* redirection_;
    PATH_TYPE* directory_;
    bool directory_listening_;
    PATH_TYPE* default_if_directory_response_path_;
    PATH_TYPE* cgi_script_path_;
    PATH_TYPE* cgi_bin_path_;

    void deleteData_();

};
