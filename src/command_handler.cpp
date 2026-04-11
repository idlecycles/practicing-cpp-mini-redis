#include "command_handler.h"

#include <optional>

namespace redis
{
    std::string handle_command(const std::vector<std::string> &parsed_command, Store &store)
    {
        const std::string &command = parsed_command[0];

        if (command == "SET")
        {
            store.set(parsed_command[1], parsed_command[2]);
            return "+OK\r\n";
        }
        else if (command == "GET")
        {
            auto value = store.get(parsed_command[1]);
            if (value.has_value())
            {
                return "$" + std::to_string(value->size()) + "\r\n" + *value + "\r\n";
            }
            return "$-1\r\n";
        }
        else if (command == "DEL")
        {
            store.del(parsed_command[1]);
            return "+OK\r\n";
        }
        else if (command == "KEYS")
        {
            auto all_keys = store.keys();
            std::string response = "*" + std::to_string(all_keys.size()) + "\r\n";
            for (const auto &key : all_keys)
            {
                response += "$" + std::to_string(key.size()) + "\r\n" + key + "\r\n";
            }
            return response;
        }
        else if (command == "EXPIRE")
        {
            store.expire(parsed_command[1], std::chrono::seconds(std::stoi(parsed_command[2])));
            return "+OK\r\n";
        }
        else if (command == "COMMAND")
        {
            return "+OK\r\n";
        }
        else
        {
            return "-ERR unknown command\r\n";
        }
    }

} // namespace redis
