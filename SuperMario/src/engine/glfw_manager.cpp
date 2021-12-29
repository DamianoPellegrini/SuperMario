#include "pch.hpp"
#include "glfw_manager.hpp"

namespace engine {
    glfw_manager::glfw_manager() : glfw_manager("Default title", 1280, 720) {}


    glfw_manager::glfw_manager(std::string title, const uint32_t width, const uint32_t height) : _title(title), _width(width), _height(height) {
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

    glfw_manager::~glfw_manager() {
        glfwDestroyWindow(this->_window);
        glfwTerminate();
    }

    void glfw_manager::run() {
        while (!glfwWindowShouldClose(this->_window)) {
            glfwPollEvents();
        }
    }


} // namespace engine
