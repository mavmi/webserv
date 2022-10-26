#pragma once

#include "utils.hpp"
#include "exceptions.hpp"

class RouteConfiguration{
public:
    typedef size_t                      SIZE_TYPE;
    typedef int                         METHOD_TYPE;
    typedef std::vector<METHOD_TYPE>    METHODS_CONTAINER_TYPE;
    typedef std::string                 PATH_TYPE;

    RouteConfiguration(){
        isDone_ = false;
        methods_ = NULL;
        redirection_ = NULL;
        directory_ = NULL;
        directory_listening_ = false;
        default_if_directory_response_path_ = NULL;
        cgi_script_path_ = NULL;
        cgi_bin_path_ = NULL;
    }
    RouteConfiguration(const RouteConfiguration& other){
        isDone_ = other.isDone_;
        methods_ = (other.methods_) ? new METHODS_CONTAINER_TYPE(*other.methods_) : NULL;
        redirection_ = (other.redirection_) ? new PATH_TYPE(*other.redirection_) : NULL;
        directory_ = (other.directory_) ? new PATH_TYPE(*other.directory_) : NULL;
        directory_listening_ = other.directory_listening_;
        default_if_directory_response_path_ = (other.default_if_directory_response_path_) ? new PATH_TYPE(*other.default_if_directory_response_path_) : NULL;
        cgi_script_path_ = (other.cgi_script_path_) ? new PATH_TYPE(*other.cgi_script_path_) : NULL;
        cgi_bin_path_ = (other.cgi_bin_path_) ? new PATH_TYPE(*other.cgi_bin_path_) : NULL;
    }
    ~RouteConfiguration(){
        deleteData_();
    }

    RouteConfiguration& operator=(const RouteConfiguration& other){
        deleteData_();

        isDone_ = other.isDone_;
        methods_ = (other.methods_) ? new METHODS_CONTAINER_TYPE(*other.methods_) : NULL;
        redirection_ = (other.redirection_) ? new PATH_TYPE(*other.redirection_) : NULL;
        directory_ = (other.directory_) ? new PATH_TYPE(*other.directory_) : NULL;
        directory_listening_ = other.directory_listening_;
        default_if_directory_response_path_ = (other.default_if_directory_response_path_) ? new PATH_TYPE(*other.default_if_directory_response_path_) : NULL;
        cgi_script_path_ = (other.cgi_script_path_) ? new PATH_TYPE(*other.cgi_script_path_) : NULL;
        cgi_bin_path_ = (other.cgi_bin_path_) ? new PATH_TYPE(*other.cgi_bin_path_) : NULL;

        return *this;        
    }

    void setMethods(const METHODS_CONTAINER_TYPE& methods){
        if (!methods_) methods_ = new METHODS_CONTAINER_TYPE(methods);
        else *methods_ = methods; 
    }
    METHODS_CONTAINER_TYPE& getMethods() const{
        if (methods_) return *methods_;
        throw RouteException("Methods are not defined", __FILE__, __FUNCTION__, __LINE__);
    }
    void setMethod(const METHOD_TYPE& method, SIZE_TYPE position){
        if (methods_) methods_->at(position) = method;
        else throw RouteException("Methods are not defined", __FILE__, __FUNCTION__, __LINE__);
    }
    METHOD_TYPE& getMethod(SIZE_TYPE position) const{
        if (methods_) return methods_->at(position);
        else throw RouteException("Methods are not defined", __FILE__, __FUNCTION__, __LINE__);
    }
    void addMethod(const METHOD_TYPE& method){
        if (!methods_) methods_ = new METHODS_CONTAINER_TYPE();
        methods_->push_back(method);
    }
    SIZE_TYPE getMethodsCount() const{
        if (methods_) return methods_->size();
        else throw RouteException("Methods are not defined", __FILE__, __FUNCTION__, __LINE__);
    }

    void setRedirection(const PATH_TYPE& redirection){
        if (!redirection_) redirection_ = new PATH_TYPE(redirection);
        else *redirection_ = redirection;
    }
    PATH_TYPE& getRedirection() const{
        if (redirection_) return *redirection_;
        throw RouteException("Redirection is not defined", __FILE__, __FUNCTION__, __LINE__);
    }

    void setDirectory(const PATH_TYPE& directory){
        if (!directory_) directory_ = new PATH_TYPE(directory);
        else *directory_ = directory;
    }
    PATH_TYPE& getDirectory() const{
        if (directory_) return *directory_;
        throw RouteException("Directory is not defined", __FILE__, __FUNCTION__, __LINE__);
    }

    void setDirectoryListening(bool directoryListening){
        directory_listening_ = directoryListening;
    }
    bool getDirectoryListening() const{
        return directory_listening_;
    }

    void setDefaultIfDirectoryResponse(const PATH_TYPE& default_if_directory_response_path){
        if (!default_if_directory_response_path_) default_if_directory_response_path_ = new PATH_TYPE(default_if_directory_response_path);
        else *default_if_directory_response_path_ = default_if_directory_response_path;
    }
    PATH_TYPE& getDefaultIfDirectoryResponse() const{
        if (default_if_directory_response_path_) return *default_if_directory_response_path_;
        throw RouteException("Default directory is not defined", __FILE__, __FUNCTION__, __LINE__);
    }

    void setCgiScriptPath(const PATH_TYPE& cgi_script_path){
        if (!cgi_script_path_) cgi_script_path_ = new PATH_TYPE(cgi_script_path);
        else *cgi_script_path_ = cgi_script_path;
    }
    PATH_TYPE& getCgiScriptPath() const{
        if (cgi_script_path_) return *cgi_script_path_;
        throw RouteException("CGI script path is not defined", __FILE__, __FUNCTION__, __LINE__);
    }

    void setCgiBinPath(const PATH_TYPE& cgi_bin_path){
        if (!cgi_bin_path_) cgi_bin_path_ = new PATH_TYPE(cgi_bin_path);
        else *cgi_bin_path_ = cgi_bin_path;
    }
    PATH_TYPE& getCgiBinPath() const{
        if (cgi_bin_path_) return *cgi_bin_path_;
        throw RouteException("CGI bin path is not defined", __FILE__, __FUNCTION__, __LINE__);
    }

    bool isDone() const{
        return isDone_;
    }
    void done(){
        isDone_ = true;
    }

private:
    bool isDone_;
    METHODS_CONTAINER_TYPE* methods_;
    PATH_TYPE* redirection_;
    PATH_TYPE* directory_;
    bool directory_listening_;
    PATH_TYPE* default_if_directory_response_path_;
    PATH_TYPE* cgi_script_path_;
    PATH_TYPE* cgi_bin_path_;

    void deleteData_(){
        delete methods_;
        delete redirection_;
        delete directory_;
        delete default_if_directory_response_path_;
        delete cgi_script_path_;
        delete cgi_bin_path_;

        isDone_ = false;
        methods_ = NULL;
        redirection_ = NULL;
        directory_ = NULL;
        directory_listening_ = false;
        default_if_directory_response_path_ = NULL;
        cgi_script_path_ = NULL;
        cgi_bin_path_ = NULL;
    }

};
