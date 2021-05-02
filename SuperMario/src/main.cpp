#include "pch.hpp"
#include <GLFW/glfw3.h>

int main(int argc, char **argv, char **envp)
{

    if (!glfwInit())
    {
        std::cerr << "Cannot initialize GLFW!" << std::endl;
        return EXIT_FAILURE;
    }

    GLFWwindow *window = glfwCreateWindow(1280, 720, "SuperMario", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetWindowSizeCallback(window, [](GLFWwindow *wnds, int width, int height) {
        glViewport(0, 0, width, height);
    });

    glfwSetErrorCallback([](int error_code, const char* description) {
        std::stringstream ss;
        ss << "OpenGLError[" << error_code << "]: " << description << std::endl;
        std::cerr << ss.str();
    });

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

		glClearColor(0.2f, 0.2f, 0.35f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
	glfwTerminate();

    return EXIT_SUCCESS;
}