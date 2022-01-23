#include "pch.hpp"
#include "application.hpp"

#include "engine/window_manager.hpp"
#include "engine/render_manager.hpp"
#include "engine/config_loader.hpp"
#include "engine/logger.hpp"

#include "config.hpp"

namespace super_mario {

    application::application() {
        std::string title = "Super Mario";
        engine::logger::init(title);
        spdlog::info("Bootstrapping application...");


        auto cfg = engine::config_loader<super_mario::config>::load_config("/Users/damiano/config.json");
        auto winman = engine::window_manager::get();
        winman->init({
            .title = title,
            .width = cfg.width,
            .height = cfg.height
            });

        // Stop application callback
        glfwSetWindowUserPointer(winman->get_window(), this);
        glfwSetWindowCloseCallback(winman->get_window(), [](GLFWwindow* window) {
            auto app = reinterpret_cast<application*>(glfwGetWindowUserPointer(window));
            app->_running = false;
        });

        auto renderman = engine::render_manager::get();
        renderman->init({
            .title = title,
            .window = winman->get_window()
            });

    }

    application::~application() {
        engine::render_manager::get()->shutdown();
        engine::window_manager::get()->shutdown();
        engine::logger::shutdown();
    }

    void application::run() {
        spdlog::info("Running application...");
        this->_running = true;

        while (this->_running) {
            glfwPollEvents();
        }
    }
} // namespace super_mario
