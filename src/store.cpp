#include "store.h"

#include <iostream>

namespace redis
{
    std::optional<std::string> Store::get(const std::string &key)
    {
        std::lock_guard<std::shared_mutex> lock(d_mutex);
        auto it = d_store.find(key);
        if (it != d_store.end())
        {
            if (d_expiry.contains(it->first))
            {
                if (d_expiry[it->first] < std::chrono::steady_clock::now())
                {
                    d_store.erase(it);
                    d_expiry.erase(key);
                    return std::nullopt;
                }
            }
            return it->second;
        }
        return std::nullopt;
    }

    void Store::set(const std::string &key, const std::string &value)
    {
        std::lock_guard<std::shared_mutex> lock(d_mutex);
        d_store[key] = value;
    }

    void Store::del(const std::string &key)
    {
        std::lock_guard<std::shared_mutex> lock(d_mutex);
        if (d_expiry.contains(key))
        {
            d_expiry.erase(key);
        }
        d_store.erase(key);
    }

    std::vector<std::string> Store::keys() const
    {
        std::shared_lock<std::shared_mutex> lock(d_mutex);
        std::vector<std::string> output;
        for (const auto& [key, value] : d_store)
        {
            output.emplace_back(key);
        }
        return output;
    }

    void Store::expire(const std::string& key, std::chrono::seconds seconds)
    {
        std::lock_guard<std::shared_mutex> lock(d_mutex);
        d_expiry[key] = std::chrono::steady_clock::now() + seconds;
    }

} // namespace redis
