#ifndef _WINDOW_MANAGER_HPP_
#define _WINDOW_MANAGER_HPP_

#include "manager.hpp"
#include "singleton.hpp"

namespace engine {

    struct window_manager_config {
        std::string title;
        uint32_t width;
        uint32_t height;
    };

    class window_manager
        : public manager<window_manager_config>,
        public singleton<window_manager> {
    private:
        window_manager_config _config;

        GLFWwindow* _window;
    public:
        virtual void init(window_manager_config config) final override;
        virtual void shutdown() final override;

        inline GLFWwindow* get_window() const { return _window; }
    };
} // namespace engine


#endif // _WINDOW_MANAGER_HPP_