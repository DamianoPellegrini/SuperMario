#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include "vulkan_manager.hpp"

namespace engine {

    class application {
    private:
        std::string _title;
        uint32_t _width;
        uint32_t _height;
        bool _running;

        // GLFW
        GLFWwindow* _window;

        const vulkan_manager* _vulkan_manager;

    public:
        application(const std::string& title, uint32_t window_width, uint32_t window_height);
        ~application();

        void run();
    private:
        void initGLFW();

        void mainLoop();

        void cleanupGLFW();
    };

} // namespace engine


#endif // _APPLICATION_HPP_