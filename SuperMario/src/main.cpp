#include "pch.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

int main(int argc, char **argv, char **envp)
{

    if (!glfwInit())
    {
        std::cerr << "Cannot initialize GLFW!" << std::endl;
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1280, 720, "SuperMario", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    if (!gladLoadGL(glfwGetProcAddress))
    {
        std::cerr << "Cannot initialize GLAD!" << std::endl;
        return EXIT_FAILURE;
    }

    glfwSetWindowSizeCallback(window, [](GLFWwindow *wnds, int width, int height) {
        glViewport(0, 0, width, height);
    });

    glfwSetErrorCallback([](int error_code, const char *description) {
        std::stringstream ss;
        ss << "OpenGLError[" << error_code << "]: " << description << std::endl;
        std::cerr << ss.str();
    });

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.2f, 0.35f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}