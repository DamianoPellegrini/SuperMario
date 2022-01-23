#include "pch.hpp"
#include "application.hpp"
#include "engine/logger.hpp"
#include "engine/config_loader.hpp"
#include "engine/window_manager.hpp"
#include "config.hpp"

int32_t main(int32_t argc, const char* argv[]) {
    int32_t exitCondition = EXIT_SUCCESS;

    super_mario::application* app = nullptr;

    try {
        app = new super_mario::application{};
        app->run();
    }
    catch (const std::exception& e) {
        spdlog::critical("{0}", e.what());
        exitCondition = EXIT_FAILURE;
    }

    delete app;

    return exitCondition;
}
