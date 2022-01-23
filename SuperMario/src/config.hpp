#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

#include "pch.hpp"

namespace super_mario {
    struct config {
        uint32_t width = 1280;
        uint32_t height = 720;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(config, width, height);
    };

} // namespace super_mario

#endif // _CONFIG_HPP_