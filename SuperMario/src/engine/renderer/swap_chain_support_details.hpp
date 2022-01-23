#ifndef _SWAP_CHAIN_SUPPORT_DETAILS_HPP
#define _SWAP_CHAIN_SUPPORT_DETAILS_HPP

#include "pch.hpp"

namespace engine::renderer {

    struct SwapChainSupportDetails {
        vk::SurfaceCapabilitiesKHR capabilities;
        std::vector<vk::SurfaceFormatKHR> formats;
        std::vector<vk::PresentModeKHR> presentModes;
    };

} // namespace engine::renderer

#endif // _SWAP_CHAIN_SUPPORT_DETAILS_HPP
