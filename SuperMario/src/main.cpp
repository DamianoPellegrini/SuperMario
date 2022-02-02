#include "pch.hpp"

#include "engine/renderer/shader.hpp"
#include "engine/renderer/buffer.hpp"
#include "engine/renderer/vertex_array.hpp"

struct WNDPTR {
    engine::renderer::vertex_buffer<float>& vb;
    const float* vertices;
    const float* vertices2;
    const size_t vertex_size;
};

struct VertexLayout {
    float x, y, z;
    float r, g, b, a;
    float s, t;
};

int main(int argc, char** argv, char** envp) {

    const uint32_t WIDTH = 1280;
    const uint32_t HEIGHT = 720;
    const bool VSYNC_ENABLE = true;

    std::clog << "Starting..." << std::endl;

    //* GLFW Initialization
    if (!glfwInit()) {
        std::cerr << "Cannot initialize GLFW!" << std::endl;
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "SuperMario", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    if (VSYNC_ENABLE) {
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

    glfwSetKeyCallback(window, [](GLFWwindow* wnds, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(wnds, true);
        }
        // glfwGetWindowUserPointer(wnds);
        // static bool state = true;

        // if (key == GLFW_KEY_V && action == GLFW_PRESS) {
        //     state = !state;
        //     glfwSwapInterval(state);
        // }

        // static bool state2 = false;

        // if (key == GLFW_KEY_B && action == GLFW_PRESS) {
        //     state2 = !state2;
        //     glPolygonMode(GL_FRONT_AND_BACK, state2 ? GL_LINE : GL_FILL);
        // }
        });

    glfwSetErrorCallback([](int error_code, const char* description) {
        std::stringstream ss;
        ss << "OpenGLError[" << error_code << "]: " << description << std::endl;
        std::cerr << ss.str();
        });

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param) {
        auto const src_str = [source]() {
            switch (source) {
            case GL_DEBUG_SOURCE_API: return "API";
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
            case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
            case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY";
            case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
            case GL_DEBUG_SOURCE_OTHER: return "OTHER";
            default: return "OTHER";
            }
        }();

        auto const type_str = [type]() {
            switch (type) {
            case GL_DEBUG_TYPE_ERROR: return "ERROR";
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
            case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
            case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
            case GL_DEBUG_TYPE_MARKER: return "MARKER";
            case GL_DEBUG_TYPE_OTHER: return "OTHER";
            default: return "OTHER";
            }
        }();

        auto const severity_str = [severity]() {
            switch (severity) {
            case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
            case GL_DEBUG_SEVERITY_LOW: return "LOW";
            case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
            case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
            default: return "UNSPECIFIED";
            }
        }();
        std::cout << src_str << ", " << type_str << ", " << severity_str << ", " << id << ": " << message << '\n';
        }, nullptr);

    // Prints driver info
    std::clog << glGetString(GL_VENDOR) << std::endl;
    std::clog << glGetString(GL_RENDERER) << std::endl;

    VertexLayout vl[4] = {
        {
            .x = -0.75f, .y = 0.75f, .z = 0.0f,
            .r = 1.0f, .g = 1.0f, .b = 0.0f, .a = 1.0f,
            .s = 0.0f, .t = 0.0f,
        },
        {
            .x = 0.75f, .y = 0.75f, .z = 0.0f,
            .r = 1.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f,
            .s = 0.0f, .t = 0.0f,
        },
        {
            .x = 0.75f, .y = -0.75f, .z = 0.0f,
            .r = 0.0f, .g = 1.0f, .b = 0.0f, .a = 1.0f,
            .s = 0.0f, .t = 0.0f,
        },
        {
            .x = -0.75f, .y = -0.75f, .z = 0.0f,
            .r = 0.0f, .g = 0.0f, .b = 1.0f, .a = 1.0f,
            .s = 0.0f, .t = 0.0f,
        },
    };

    uint32_t indices[6] = {
        // Upper triangle
        0, 1, 3,

        // Lower triangle
        1, 2, 3,
    };

    {
        //* VAO Configuration
        engine::renderer::vertex_array vao{};

        engine::renderer::vertex_buffer<float> vbo{ (float*)&vl, sizeof(vl) / sizeof(float), GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT | GL_MAP_READ_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT };
        // vbo.bind();
        vao.define_attribute(vbo, 0, 3, false, 9 * sizeof(float), 0);
        vao.enable_attribute(0);
        vao.define_attribute(vbo, 1, 4, false, 9 * sizeof(float), 3 * sizeof(float));
        vao.enable_attribute(1);
        vao.define_attribute(vbo, 2, 2, false, 9 * sizeof(float), 4 * sizeof(float));
        vao.enable_attribute(2);

        engine::renderer::index_buffer<uint32_t> ibo{ indices, sizeof(indices) / sizeof(uint32_t), GL_DYNAMIC_STORAGE_BIT };
        // ibo.bind(); // Same as below
        vao.bind_index_buffer(ibo);

        vao.bind();


        //* Shader Initialization
        engine::renderer::shader basic_shader{
            "assets/shaders/basic.vs",
            "assets/shaders/basic.fs"
        };
        basic_shader.bind();

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

            // basic_shader.set_uniform("tint", glm::vec3(0.0f, 0.0f, abs(sin(currentFrameTime*2)) * 0.5f));

            glfwPollEvents();

            glClearColor(.2f, .2f, .25f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(uint32_t), GL_UNSIGNED_INT, 0);

            glfwSwapBuffers(window);
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}