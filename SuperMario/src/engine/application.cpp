#include "pch.hpp"
#include "application.hpp"

namespace engine {

    application::application(const std::string& title, uint32_t width, uint32_t height)
        : _title(title), _width(width), _height(height) {
        initGLFW();

        auto fut = std::async(std::launch::async, [](const std::string& title) {
            return new vulkan_manager(title);
            }, title);

        this->_vulkan_manager = fut.get();

    }

    application::~application() {
        delete _vulkan_manager;
        cleanupGLFW();
    }

    void application::run() {
        mainLoop();
    }

    void application::mainLoop() {
        while (!glfwWindowShouldClose(_window)) {
            glfwPollEvents();
        }
    }

    void application::initGLFW() {
        if (glfwInit() != GLFW_TRUE)
            throw std::runtime_error("Failed to initialize GLFW!");
        // Disable default OpenGL Context creation
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
#ifdef DEBUG
        glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
#else
        glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
#endif
        // glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
        // glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
        this->_window = glfwCreateWindow(this->_width, this->_height, this->_title.c_str(), nullptr, nullptr);
    }

    void application::cleanupGLFW() {
        glfwDestroyWindow(this->_window);
        glfwTerminate();
    }

} // namespace engine
