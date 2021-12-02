#include "pch.hpp"
#include "engine/application.hpp"

int32_t main(int32_t argc, const char* argv[]) {
    int32_t exitCondition = EXIT_SUCCESS;
    engine::application* app = new engine::application{
        "Super Mario",
        1280,
        720
    };

    try {
        app->run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        exitCondition = EXIT_FAILURE;
    }

    delete app;

    return exitCondition;
}