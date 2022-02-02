#ifndef _UTIL_HPP
#define _UTIL_HPP

#include "pch.hpp"

namespace engine::util {

    template<class T>
    inline GLenum getGLType() {
        return GL_NONE;
    };

    // GL_BYTE
    template<>
    inline GLenum getGLType<int8_t>() {
        return GL_BYTE;
    };

    template<>
    inline GLenum getGLType<uint8_t>() {
        return GL_UNSIGNED_BYTE;
    };

    // GL_SHORT
    template<>
    inline GLenum getGLType<int16_t>() {
        return GL_SHORT;
    };

    template<>
    inline GLenum getGLType<uint16_t>() {
        return GL_UNSIGNED_SHORT;
    };

    // GL_INT
    template<>
    inline GLenum getGLType<int32_t>() {
        return GL_INT;
    };

    template<>
    inline GLenum getGLType<uint32_t>() {
        return GL_UNSIGNED_INT;
    };

    // GL_FLOAT
    template<>
    inline GLenum getGLType<float_t>() {
        return GL_FLOAT;
    };

    // GL_DOUBLE
    template<>
    inline GLenum getGLType<double_t>() {
        return GL_DOUBLE;
    };
} // namespace engine::util

#endif // _UTIL_HPP
