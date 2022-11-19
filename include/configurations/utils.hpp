#pragma once

#include <set>
#include <cctype>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <utility>
#include <stdint.h>
#include <algorithm>

#include "../utils.hpp"

namespace configuration {

enum CONFIG_ELEM{
    PORT,
    HOST,
    SERVER_NAME,
    ERROR_PAGES,
    BODY_SIZE,
    METHODS,
    REDIR,
    DIR,
    DIR_LISTENING,
    DEF_IF_DIR,
    CGI_SCRIPT,
    CGI_BIN
};

enum HTTP_METHOD{
    GET,
    POST,
    DELETE
};

class Configuration;
class ServerConfiguration;
class RouteConfiguration;
template <typename T> class Container;

}
