#ifndef _CONFIG_LOADER_CPP_
#define _CONFIG_LOADER_CPP_
#include "pch.hpp"
#include "config_loader.hpp"

namespace engine {
    template<class T>
    T config_loader<T>::load_config(const std::filesystem::path& path) {
        std::ifstream file{ path };

        // If file doesn't exist, create it with defaults.
        if (!file.is_open()) {
            T def_cfg = T{};
            config_loader::save_config(path, def_cfg);
            return def_cfg;
        }

        auto j = nlohmann::json::parse(file);
        file.close();
        return j.get<T>();
    }

    template<class T>
    void config_loader<T>::save_config(const std::filesystem::path& path, const T& config) {
        std::ofstream file{ path, std::ios::out | std::ios::trunc };

        if (!file.is_open())
            throw std::runtime_error{ "Failed to open file: " + path.string() };

        nlohmann::json j = config;

        file << j;
        file.close();
    }
} // namespace engine

#endif // _CONFIG_LOADER_CPP_
