#ifndef _QUEUE_FAMILY_INDICES_HPP
#define _QUEUE_FAMILY_INDICES_HPP

#include "pch.hpp"

namespace engine::renderer {
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;
        std::optional<uint32_t> transferFamily;
        std::optional<uint32_t> computeFamily;


        bool isComplete() {
            return graphicsFamily.has_value() &&
                presentFamily.has_value() &&
                transferFamily.has_value() &&
                computeFamily.has_value();
        }
    };

} // namespace engine::renderer

#endif // _QUEUE_FAMILY_INDICES_HPP
