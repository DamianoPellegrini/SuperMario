#include "pch.hpp"
#include "application.hpp"

#include "engine/modules/window_manager.hpp"
#include "engine/modules/config_loader.hpp"
#include "engine/modules/logger.hpp"

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

        this->_vulkan_manager = std::make_unique<engine::vulkan_manager>(title, winman->get_window());
    }

    application::~application() {


        // !! shutdown logger after every manager had shutdown
        engine::window_manager::get()->shutdown();
        // engine::logger::shutdown();
    }

    void application::run() {
        spdlog::info("Running application...");
        this->_running = true;

        while (!glfwWindowShouldClose(engine::window_manager::get()->get_window())) {
            glfwPollEvents();
        }
    }
} // namespace super_mario
