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
        : public manager<std::string, uint32_t, uint32_t>,
        public singleton<window_manager> {
    private:
        std::string _title;
        uint32_t _width;
        uint32_t _height;

        GLFWwindow* _window;
    public:
        virtual void init(std::string title, uint32_t width, uint32_t height) final override;
        virtual void shutdown() final override;

        inline GLFWwindow* get_window() const { return _window; }
    };
} // namespace engine


#endif // _WINDOW_MANAGER_HPP_