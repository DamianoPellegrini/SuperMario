#include "pch.hpp"
#include "logger.hpp"

namespace engine {

    void logger::init(std::string name) {
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_level(spdlog::level::debug);

        auto file_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>("logs/" + name + ".log", 0, 0);
        file_sink->set_level(spdlog::level::warn);

        auto logger = std::shared_ptr<spdlog::logger>(new spdlog::logger(name, { console_sink, file_sink }));
        logger->set_level(spdlog::level::debug);

        spdlog::set_default_logger(logger);
        spdlog::info("Logger initialized!");
    }

    void logger::shutdown() {
        spdlog::info("Logger shutting down...");
        spdlog::shutdown();
    }
} // namespace engine
