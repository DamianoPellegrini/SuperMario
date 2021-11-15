#ifndef _BUFFER_HPP
#define _BUFFER_HPP

namespace engine::renderer {
    template<GLenum target, class T>
    class buffer {
    protected:
        uint32_t buffer_id;

    public:
        buffer(const T* data, size_t count, GLenum usage = GL_STATIC_DRAW);
        virtual ~buffer();

        virtual void bind() const;
        virtual void unbind() const;

        inline virtual uint32_t id() const { return buffer_id; };
    };

    template<GLenum target, class T>
    buffer<target, T>::buffer(const T* data, size_t count, GLenum usage) {
        glGenBuffers(1, &buffer_id);
        this->bind();
        // Write to the currenctly bound 'target' buffer
        glBufferData(target, count * sizeof(T), data, usage);
        this->unbind();
    }

    template<GLenum target, class T>
    void buffer<target, T>::bind() const {
        glBindBuffer(target, buffer_id);
    }

    template<GLenum target, class T>
    void buffer<target, T>::unbind() const {
        glBindBuffer(target, 0);
    }

    template<GLenum target, class T>
    buffer<target, T>::~buffer() {
        glDeleteBuffers(1, &buffer_id);
    }

    template<class T>
    using vertex_buffer = buffer<GL_ARRAY_BUFFER, T>;

    template<class T>
    using index_buffer = buffer<GL_ELEMENT_ARRAY_BUFFER, T>;
} // namespace engine::renderer

#endif