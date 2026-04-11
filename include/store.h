#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <optional>

namespace redis
{
    class Store
    {
        public:
            std::optional<std::string> get(const std::string& key) const;
            void set(const std::string& key, const std::string& value);
            void del(const std::string& key);
            std::vector<std::string> keys() const;

        private:
            std::unordered_map<std::string, std::string> d_store;
    };

} // namespace redis
