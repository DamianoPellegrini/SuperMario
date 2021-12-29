#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

#include "vulkan_manager.hpp"
#include "glfw_manager.hpp"

namespace engine {

    class application {
    private:

        std::shared_ptr<spdlog::logger> _logger = nullptr;

        bool _running;

        std::unique_ptr<vulkan_manager> _vulkan_manager = nullptr;
        std::unique_ptr<glfw_manager> _glfw_manager = nullptr;
    public:
        application(const std::string& title, const uint32_t window_width, const uint32_t window_height);
        ~application();

        void run();
        void init_logger(const std::string& title);
    private:
    };

} // namespace engine


#endif // _APPLICATION_HPP_