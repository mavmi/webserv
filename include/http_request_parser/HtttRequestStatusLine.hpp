#pragma once

#include "utils.hpp"

namespace MAIN_NAMESPACE::HTTP_REQUEST_PARS_NAMESPACE{

class HttpRequestStatusLine{
friend HttpRequestParser;
public:
    ~HttpRequestStatusLine();

private:
    /*
        Bunch of wrappers must be here
    */

    HttpRequestStatusLine();
    HttpRequestStatusLine(const HttpRequestStatusLine& other);

    HttpRequestStatusLine& operator=(const HttpRequestStatusLine& other);

};

}
