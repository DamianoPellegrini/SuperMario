#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include "vulkan_manager.hpp"
#include "glfw_manager.hpp"

namespace engine {

    class application {
    private:
        bool _running;

        vulkan_manager* _vulkan_manager;
        glfw_manager* _glfw_manager;
    public:
        application(const std::string& title, const uint32_t window_width, const uint32_t window_height);
        ~application();

        void run();
    private:
    };

} // namespace engine


#endif // _APPLICATION_HPP_