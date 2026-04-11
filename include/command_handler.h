#pragma once

#include <string>
#include <vector>

#include "store.h"

namespace redis
{
    std::string handle_command(const std::vector<std::string> &parsed_command, Store &store);

} // namespace redis
