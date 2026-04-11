#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <optional>
#include <mutex>
#include <shared_mutex>
#include <chrono>

namespace redis
{
    class Store
    {
        public:
            std::optional<std::string> get(const std::string& key);
            void set(const std::string& key, const std::string& value);
            void del(const std::string& key);
            void expire(const std::string& key, std::chrono::seconds seconds);
            std::vector<std::string> keys() const;

        private:
            mutable std::shared_mutex d_mutex;
            std::unordered_map<std::string, std::string> d_store;
            std::unordered_map<std::string, std::chrono::steady_clock::time_point> d_expiry;
    };

} // namespace redis
