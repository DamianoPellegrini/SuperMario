#include "pch.hpp"

#include "engine/renderer/shader.hpp"
#include "engine/renderer/buffer.hpp"
#include "engine/renderer/vertex_array.hpp"

int main(int argc, char** argv, char** envp) {

    std::clog << "Starting..." << std::endl;

    simdjson::dom::parser parser;
    auto config = parser.load("config.json").get_object();


    if (auto configError = config.error()) {
        std::cerr << "Error while loading the configuration: " << configError << std::endl;
        return EXIT_FAILURE;
    }

    std::clog << "Configuration loaded successfully" << std::endl;

    //* GLFW Initialization
    if (!glfwInit()) {
        std::cerr << "Cannot initialize GLFW!" << std::endl;
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(config["width"].get_uint64(), config["height"].get_uint64(), "SuperMario", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    if (config["vsync"].get<bool>()) {
        glfwSwapInterval(1);
    }
    else {
        glfwSwapInterval(0);
    }

    if (!gladLoadGL(glfwGetProcAddress)) {
        std::cerr << "Cannot initialize GLAD!" << std::endl;
        return EXIT_FAILURE;
    }

    glfwSetWindowSizeCallback(window, [](GLFWwindow* wnds, int width, int height) {
        glViewport(0, 0, width, height);
        });

    glfwSetErrorCallback([](int error_code, const char* description) {
        std::stringstream ss;
        ss << "OpenGLError[" << error_code << "]: " << description << std::endl;
        std::cerr << ss.str();
        });

    // Prints driver info
    std::clog << glGetString(GL_VENDOR) << std::endl;
    std::clog << glGetString(GL_RENDERER) << std::endl;

    float vertices[12] = {
        // Top left
        -0.75f,
        0.75f,
        0.0f,

        // Top right
        0.75f,
        0.75f,
        0.0f,

        // Bottom right
        0.75f,
        -0.75f,
        0.0f,

        // Bottom left
        -0.75f,
        -0.75f,
        0.0f,
    };

    uint32_t indices[6] = {
        // Upper triangle
        0,
        1,
        3,

        // Lower triangle
        1,
        2,
        3,

    };

    {
        engine::renderer::vertex_array vao{};
        vao.bind();
        vao.enable_attribute(0);

        engine::renderer::vertex_buffer<float> vbo{ vertices, 12, GL_STATIC_DRAW };
        vbo.bind();
        vao.define_attribute(vbo, 0, 3, false, 3 * sizeof(float), 0);

        engine::renderer::index_buffer<uint32_t> ibo{ indices, 6, GL_STATIC_DRAW };
        // ibo.bind(); // Same as below
        vao.bind_element_buffer(ibo);

        //* Shader Initialization
        engine::renderer::shader shader{
            "assets/shaders/vertex.glsl",
            "assets/shaders/fragment.glsl"
        };
        shader.use();

        float lastFrameTime = glfwGetTime();
        float test = .0f;
        //* MAIN LOOP
        while (!glfwWindowShouldClose(window)) {

            float currentFrameTime = glfwGetTime();
            float deltaTime = currentFrameTime - lastFrameTime;
            lastFrameTime = currentFrameTime;


            test += deltaTime;
            // Every half second print stats
            if (test >= 0.5f) {
                std::cout << "FPS: " << (int32_t)(1.0f / deltaTime) << std::endl;
                std::cout << "Frametime (ms): " << std::fixed << deltaTime << std::endl;
                test = .0f;
            }

            // glUniform3f(glGetUniformLocation(shader.handle(), "tint"), 0.0f, 0.0f, abs(sin(currentFrameTime)) * 0.5f);

            glfwPollEvents();

            glClearColor(.2f /* * abs(sin(glfwGetTime())) */, .2f, .25f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            glfwSwapBuffers(window);
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}