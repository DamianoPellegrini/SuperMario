#include "pch.hpp"
#include "shader.hpp"

#define SHADER_ASYNC 1

namespace engine::renderer {

    std::string loadShader(const std::filesystem::path& shader_path) {
        std::ostringstream shader_stream;
        std::ifstream shader_file{ shader_path };
        shader_stream << shader_file.rdbuf();
        shader_file.close();
        return shader_stream.str();
    }

    shader::shader(const std::filesystem::path& vertex_path, const std::filesystem::path& fragment_path) {
        // Vertex shader
#if SHADER_ASYNC == 1
        auto vertex_source$ = std::async(std::launch::async, loadShader, vertex_path);
        auto fragment_source$ = std::async(std::launch::async, loadShader, fragment_path);
        auto vertex_source = vertex_source$.get();
#else
        auto vertex_source = loadShader(vertex_path);
#endif
        auto vertex_source_ptr = vertex_source.c_str();

        uint32_t vertex_id = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_id, 1, &vertex_source_ptr, nullptr);
        glCompileShader(vertex_id);

        int shaderSuccess;
        glGetShaderiv(vertex_id, GL_COMPILE_STATUS, &shaderSuccess);

        if (!shaderSuccess) {
            char shaderInfoLog[512];
            glGetShaderInfoLog(vertex_id, 512, nullptr, shaderInfoLog);
            throw std::runtime_error{ shaderInfoLog };
        }

        // Fragment shader
#if SHADER_ASYNC == 1
        auto fragment_source = fragment_source$.get();
#else
        auto fragment_source = loadShader(fragment_path);
#endif
        auto fragment_source_ptr = fragment_source.c_str();

        uint32_t fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_id, 1, &fragment_source_ptr, nullptr);
        glCompileShader(fragment_id);

        glGetShaderiv(fragment_id, GL_COMPILE_STATUS, &shaderSuccess);

        if (!shaderSuccess) {
            char shaderInfoLog[512];
            glGetShaderInfoLog(fragment_id, 512, nullptr, shaderInfoLog);
            throw std::runtime_error{ shaderInfoLog };
        }

        this->shader_id = glCreateProgram();
        glAttachShader(this->shader_id, vertex_id);
        glAttachShader(this->shader_id, fragment_id);
        glLinkProgram(this->shader_id);

        glGetProgramiv(this->shader_id, GL_LINK_STATUS, &shaderSuccess);

        if (!shaderSuccess) {
            char shaderInfoLog[512];
            glGetProgramInfoLog(this->shader_id, 512, nullptr, shaderInfoLog);
            throw std::runtime_error{ shaderInfoLog };
        }

        glDeleteShader(vertex_id);
        glDeleteShader(fragment_id);
    }

    shader::~shader() {
        glDeleteProgram(this->shader_id);
    }

    void shader::use() const {
        glUseProgram(this->shader_id);
    }
} // namespace engine::renderer