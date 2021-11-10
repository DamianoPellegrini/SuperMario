#include "pch.hpp"

#include "engine/renderer/shader.hpp"

int main(int argc, char** argv, char** envp) {
    simdjson::dom::parser parser;
    auto config = parser.load("config.json").get_object();


    if (auto configError = config.error()) {
        std::cerr << "Error while loading the configuration: " << configError << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Configuration loaded successfully" << std::endl;

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
    std::cout << glGetString(GL_VENDOR) << std::endl;
    std::cout << glGetString(GL_RENDERER) << std::endl;

    float vertices[12] = {
        // Top left
        -0.5f,
        0.5f,
        0.0f,

        // Top right
        0.5f,
        0.5f,
        0.0f,

        // Bottom right
        0.5f,
        -0.5f,
        0.0f,

        //Bottom left
        -0.5f,
        -0.5f,
        0.0f,
    };

    unsigned int indices[6] = {
        // First triangle
        0,
        1,
        3,

        // Second triangle
        1,
        2,
        3,

    };

    uint vaoId;
    glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    uint vboId;
    glGenBuffers(1, &vboId);
    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    uint iboId;
    glGenBuffers(1, &iboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    {
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

            glfwPollEvents();

            test += deltaTime;
            if (test >= .25f) {
                std::cout << "FPS: " << (int32_t)(1.0f / deltaTime) << std::endl;
                std::cout << "Frametime (ms): " << std::fixed << deltaTime << std::endl;
                test = .0f;
            }

            glClearColor(.2f * abs(sin(glfwGetTime())), .2f, .25f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            glfwSwapBuffers(window);
        }
    }

    glDeleteBuffers(1, &iboId);
    glDeleteBuffers(1, &vboId);
    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}