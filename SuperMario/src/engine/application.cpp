#include "pch.hpp"
#include "application.hpp"

namespace engine {

    application::application(const std::string& title, uint32_t width, uint32_t height) {

        std::future<glfw_manager*> glfwFut = std::async(std::launch::async, [](const std::string& title, const uint32_t width, const uint32_t height) {
            return new glfw_manager(title, width, height);
            }, title, width, height);

        std::future<vulkan_manager*> vulkanFut = std::async(std::launch::async, [](const std::string& title) {
            return new vulkan_manager(title);
            }, title);

        this->_glfw_manager = glfwFut.get();
        this->_vulkan_manager = vulkanFut.get();

    }

    application::~application() {}

    void application::run() {
        this->_glfw_manager->run();
    }
} // namespace engine
