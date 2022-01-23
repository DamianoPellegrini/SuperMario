#include "pch.hpp"
#include "render_manager.hpp"

namespace engine {
    void render_manager::init(render_manager_config config)     {
        spdlog::info("Initializing render manager...");
    }

    void render_manager::shutdown() {
        spdlog::info("Shutting down render manager...");
    }
} // namespace engine
