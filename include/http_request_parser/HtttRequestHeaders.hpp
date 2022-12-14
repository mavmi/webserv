#pragma once

#include "utils.hpp"

namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{

class HttpRequestHeaders{
friend HttpRequestParser;
public:
    ~HttpRequestHeaders();

private:
    /*
        Bunch of wrappers must be here
    */

    HttpRequestHeaders();
    HttpRequestHeaders(const HttpRequestHeaders& other);

    HttpRequestHeaders& operator=(const HttpRequestHeaders& other);

};

}
