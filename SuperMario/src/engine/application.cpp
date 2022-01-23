#include "pch.hpp"
#include "application.hpp"

namespace engine {

    application::application(const std::string& title, uint32_t width, uint32_t height) {
        spdlog::info("Bootstrapping application...");

        spdlog::warn("Application bootstrapped!");
        this->_glfw_manager = std::make_shared<glfw_manager>(title, width, height);
        this->_vulkan_manager = std::make_unique<vulkan_manager>(title, this->_glfw_manager);
    }

    application::~application() {}

    void application::run() {
        this->_glfw_manager->run();
    }
} // namespace engine
