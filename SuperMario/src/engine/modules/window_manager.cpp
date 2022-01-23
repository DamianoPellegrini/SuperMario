#include "pch.hpp"
#include "window_manager.hpp"

namespace engine {
    void window_manager::init(window_manager_config config) {
        spdlog::info("Initializing window manager...");

        this->_config = config;

        if (glfwInit() != GLFW_TRUE)
            throw std::runtime_error("Failed to initialize GLFW!");

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
#ifdef DEBUG
        glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
#else
        glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
#endif

        this->_initialized = true;
        this->_window = glfwCreateWindow(config.width, config.height, config.title.c_str(), nullptr, nullptr);
    }

    void window_manager::shutdown() {
        spdlog::info("Shutting down window manager...");

        glfwDestroyWindow(this->_window);
        glfwTerminate();
        this->_initialized = false;
    }
} // namespace engine
