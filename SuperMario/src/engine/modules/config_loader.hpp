#ifndef _CONFIG_LOADER_HPP_
#define _CONFIG_LOADER_HPP_


namespace engine {
    template<class T>
    class config_loader {
    public:
        static T load_config(const std::filesystem::path& path);
        static void save_config(const std::filesystem::path& path, const T& config);
    };
} // namespace engine

#include "config_loader.cpp"

#endif // _CONFIG_LOADER_HPP_