#pragma once

#include <vector>
#include <stddef.h>

class HttpRequestParser{
public:
    typedef size_t      SizeType;
    typedef char*       BufferType;

    ~HttpRequestParser();

    static HttpRequestParser parseHttpRequest(const std::vector<char *>& buffer);

    void clear();

private:
    HttpRequestParser();
    HttpRequestParser(const HttpRequestParser& other);

    HttpRequestParser& operator=(const HttpRequestParser& other);

};
