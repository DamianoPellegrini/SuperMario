#include "pch.hpp"
#include "application.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>

namespace engine {

    application::application(const std::string& title, uint32_t width, uint32_t height) {

        this->init_logger(title);
        spdlog::info("Bootstrapping application...");
        // std::future<glfw_manager*> glfwFut = std::async(std::launch::async, [](const std::string& title, const uint32_t width, const uint32_t height) {
        //     return new glfw_manager(title, width, height);
        //     }, title, width, height);

        // std::future<vulkan_manager*> vulkanFut = std::async(std::launch::async, [](const std::string& title) {
        //     return new vulkan_manager(title);
        //     }, title);

        // this->_glfw_manager = glfwFut.get();
        // this->_vulkan_manager = vulkanFut.get();

        spdlog::warn("Application bootstrapped!");
        this->_glfw_manager = std::make_unique<glfw_manager>(title, width, height);
        this->_vulkan_manager = std::make_unique<vulkan_manager>(title);
    }

    application::~application() {}

    void application::run() {
        this->_glfw_manager->run();
    }

    void application::init_logger(const std::string& title) {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::debug);

        auto file_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>("logs/" + title + ".log", 0, 0);
        file_sink->set_level(spdlog::level::warn);

        this->_logger = std::shared_ptr<spdlog::logger>(new spdlog::logger(title, { console_sink, file_sink }));
        this->_logger->set_level(spdlog::level::debug);

        spdlog::set_default_logger(this->_logger);
    }
} // namespace engine
