#ifndef _QUEUE_FAMILY_INDICES_HPP
#define _QUEUE_FAMILY_INDICES_HPP

#include "pch.hpp"

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;

    bool isComplete() {
        return graphicsFamily.has_value();
    }
};

#endif // _QUEUE_FAMILY_INDICES_HPP
