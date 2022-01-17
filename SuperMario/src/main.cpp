#include "pch.hpp"
#include "engine/application.hpp"

int32_t main(int32_t argc, const char* argv[]) {
    int32_t exitCondition = EXIT_SUCCESS;

    // TODO: Detach logger initialization from application so
    // that it can flush the log if the application crash and
    // the log instance is destroyed.
    engine::application* app = nullptr;

    try {
        app = new engine::application{
            "Super Mario",
            1280,
            720
        };
        app->run();
    }
    catch (const std::exception& e) {
        spdlog::critical("{0}", e.what());
        exitCondition = EXIT_FAILURE;
    }

    delete app;

    spdlog::shutdown();

    return exitCondition;
}
