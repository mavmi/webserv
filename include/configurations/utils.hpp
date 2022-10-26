#pragma once

#include <set>
#include <cctype>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <utility>
#include <algorithm>

#include "../utils.hpp"

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
