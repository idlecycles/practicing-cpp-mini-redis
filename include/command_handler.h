#pragma once

#include <string>
#include <vector>

#include "store.h"

namespace redis
{
    std::string command_handler(const std::vector<std::string> &parsed_command, Store &store);

} // namespace redis
