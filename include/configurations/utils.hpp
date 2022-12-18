#pragma once

#include <set>
#include <map>
#include <cctype>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <utility>
#include <stdint.h>
#include <typeinfo>
#include <algorithm>

#include "../utils/utils.hpp"
#include "../utils/wrapper.hpp"
#include "../utils/container.hpp"
#include "../utils/exceptions.hpp"
#include "../utils/parserAbstractParent.hpp"

namespace MAIN_NAMESPACE{

class Parser;

namespace CONFIG_NAMESPACE {
class Configuration;
class ServerConfiguration;
class RouteConfiguration;
} // namespace configuration

namespace CONFIG_NAMESPACE {
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
} // namespace configuration

} // namespace wsrv
