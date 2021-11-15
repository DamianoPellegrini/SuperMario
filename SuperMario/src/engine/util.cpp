#include "pch.hpp"
#include "util.hpp"

namespace engine::util {

    // GL_BYTE
    template<>
    GLenum getGLType<int8_t>() {
        return GL_BYTE;
    };

    template<>
    GLenum getGLType<uint8_t>() {
        return GL_UNSIGNED_BYTE;
    };

    // GL_SHORT
    template<>
    GLenum getGLType<int16_t>() {
        return GL_SHORT;
    };

    template<>
    GLenum getGLType<uint16_t>() {
        return GL_UNSIGNED_SHORT;
    };

    // GL_INT
    template<>
    GLenum getGLType<int32_t>() {
        return GL_INT;
    };

    template<>
    GLenum getGLType<uint32_t>() {
        return GL_UNSIGNED_INT;
    };

    // GL_FLOAT
    template<>
    GLenum getGLType<float_t>() {
        return GL_FLOAT;
    };

    // GL_DOUBLE
    template<>
    GLenum getGLType<double_t>() {
        return GL_DOUBLE;
    };

} // namespace engine::renderer