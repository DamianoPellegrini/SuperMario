#include "pch.hpp"
#include "engine/application.hpp"

int main() {
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
        return EXIT_FAILURE;
    }

    delete app;

    return EXIT_SUCCESS;
}