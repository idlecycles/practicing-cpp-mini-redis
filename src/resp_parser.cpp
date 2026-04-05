#include "resp_parser.h"
#include <sstream>

namespace redis
{
    std::vector<std::string> parse_resp(const std::string &raw)
    {
        std::vector<std::string> commands{};
        std::istringstream iss(raw);
        std::string line;

        // read *N line
        std::getline(iss, line);
        int count = std::stoi(line.substr(1));

        for (int i = 0; i < count; i++)
        {
            // skip $len line
            std::getline(iss, line);

            // read the actual string
            std::getline(iss, line);

            // strip trailing \r
            if (!line.empty() && line.back() == '\r')
            {
                line.pop_back();
            }

            commands.push_back(line);
        }

        return commands;
    }
} // namespace redis
