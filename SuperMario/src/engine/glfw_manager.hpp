#ifndef _GLFW_MANAGER_HPP_
#define _GLFW_MANAGER_HPP_

#include "old_manager.hpp"

namespace engine {
    class glfw_manager : public old_manager {
    private:
        std::string _title;
        uint32_t _width;
        uint32_t _height;

        GLFWwindow* _window;

    public:
        glfw_manager();
        glfw_manager(std::string title, const uint32_t width, const uint32_t height);
        virtual ~glfw_manager() override;

        virtual void run() override;

        inline GLFWwindow* get_window() const { return _window; }
    private:
    };
} // namespace engine


#endif // _GLFW_MANAGER_HPP_