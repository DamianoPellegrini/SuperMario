#include "pch.hpp"
#include "engine/application.hpp"
#include "engine/modules/logger.hpp"
#include "engine/modules/config_loader.hpp"
#include "engine/modules/window_manager.hpp"
#include "config.hpp"

int32_t main(int32_t argc, const char* argv[]) {
    int32_t exitCondition = EXIT_SUCCESS;

    std::string appTitle = "Super Mario";

    engine::logger::init(appTitle);

    auto cfg = engine::config_loader<super_mario::config>::load_config("/Users/damiano/config.json");

    auto winman = engine::window_manager::get();
    winman->init("WINDOW::MANAGER::TEST", cfg.width, cfg.height);
    assert(winman->is_initialized() && winman->get_window() != nullptr);

    engine::application* app = nullptr;

    try {
        app = new engine::application{
            appTitle,
            cfg.width,
            cfg.height
        };
        app->run();
    }
    catch (const std::exception& e) {
        spdlog::critical("{0}", e.what());
        exitCondition = EXIT_FAILURE;
    }

    delete app;

    engine::logger::shutdown();

    return exitCondition;
}
