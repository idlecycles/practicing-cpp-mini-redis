#pragma once

#include <vector>
#include <string>

namespace redis
{
    std::vector<std::string> parse_resp(const std::string &raw);
    
} // namespace redis
