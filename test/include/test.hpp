#pragma once

#include "test_utils.hpp"
#include "../../include/configurations/configuration.hpp"
#include "../../include/configurations/configuration_host.hpp"

#define ___HEADER___ TestHeader(__FUNCTION__);

namespace test{

void CONFIGURATION_HOST_TESTS();
void FILES_TESTS();

}

void RUN_ALL_TESTS();
