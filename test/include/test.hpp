#pragma once

#include "test_utils.hpp"
#include "../../include/configurations/parser.hpp"
#include "../../include/http_request_parser/http_request_parser.hpp"

#define ___HEADER___ TestHeader(__FUNCTION__);

namespace test{

void CONFIGURATION_HOST_TESTS();
void CONFIGURATION_FILES_TESTS();
void HTTP_REQUEST_FILE_TEST();
void ARRAY_CONTAINER_TEST();

}

void RUN_ALL_TESTS();
