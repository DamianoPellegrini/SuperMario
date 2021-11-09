#include "pch.hpp"

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

#pragma region Shader

    const char* vertexShaderSource = "#version 460 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main(){\n"
        "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}";

    unsigned int vertexShaderId;
    vertexShaderId = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShaderId, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShaderId);

    int shaderSuccess;
    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &shaderSuccess);

    if (!shaderSuccess) {
        char shaderInfoLog[512];
        glGetShaderInfoLog(vertexShaderId, 512, nullptr, shaderInfoLog);
        std::cerr << "[Error](OpenGL) Compile vertex shader failed: " << shaderInfoLog << std::endl;
    }

    const char* fragmentShaderSource = "#version 460 core\n"
        "out vec4 FragColor;\n"
        "void main(){\n"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}";

    unsigned int fragmentShaderId;
    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShaderId);

    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &shaderSuccess);

    if (!shaderSuccess) {
        char shaderInfoLog[512];
        glGetShaderInfoLog(fragmentShaderId, 512, nullptr, shaderInfoLog);
        std::cerr << "[Error](OpenGL) Compile fragment shader failed: " << shaderInfoLog << std::endl;
    }

    unsigned int shaderProgramId;
    shaderProgramId = glCreateProgram();

    glAttachShader(shaderProgramId, vertexShaderId);
    glAttachShader(shaderProgramId, fragmentShaderId);
    glLinkProgram(shaderProgramId);

    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &shaderSuccess);

    if (!shaderSuccess) {
        char shaderInfoLog[512];
        glGetProgramInfoLog(shaderProgramId, 512, nullptr, shaderInfoLog);
        std::cerr << "[Error](OpenGL) Compile shader program failed: " << shaderInfoLog << std::endl;
    }

    glUseProgram(shaderProgramId);
    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

#pragma endregion

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

    //* MAIN LOOP
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.2f, 0.2f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}