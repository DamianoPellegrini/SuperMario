#ifndef _BUFFER_HPP
#define _BUFFER_HPP

namespace engine::renderer {
    template<GLenum target, class T>
    class buffer {
    protected:
        uint32_t buffer_id;
        void* gpu_memory_ptr;
    public:
        buffer(const T* data, size_t count, GLenum usage = GL_STATIC_DRAW);
        virtual ~buffer();

        virtual void bind() const;
        virtual void unbind() const;
        virtual void write(const T* data, const size_t size) const;

        inline virtual uint32_t id() const { return buffer_id; };
    };

    template<GLenum target, class T>
    buffer<target, T>::buffer(const T* data, size_t count, GLenum usage) {
#if GL_ARB_direct_state_access
        glCreateBuffers(1, &buffer_id);
        glNamedBufferStorage(this->buffer_id, count * sizeof(T), data, usage);
        if (usage & (GL_MAP_WRITE_BIT | GL_MAP_READ_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT))
            gpu_memory_ptr = glMapNamedBuffer(this->buffer_id, GL_READ_WRITE);
#else
        glGenBuffers(1, &buffer_id);
        this->bind();
        // Write to the currenctly bound 'target' buffer
        glBufferStorage(target, count * sizeof(T), data, usage);
        this->unbind();
#endif
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
    void buffer<target, T>::write(const T* data, const size_t size) const {
        if (!this->gpu_memory_ptr) return;
        memcpy(this->gpu_memory_ptr, data, size);
    }

    template<GLenum target, class T>
    buffer<target, T>::~buffer() {
        if (this->gpu_memory_ptr) {
            glUnmapNamedBuffer(this->buffer_id);
            this->gpu_memory_ptr = nullptr;
        }
        glDeleteBuffers(1, &buffer_id);
    }

    template<class T>
    using vertex_buffer = buffer<GL_ARRAY_BUFFER, T>;

    template<class T>
    using index_buffer = buffer<GL_ELEMENT_ARRAY_BUFFER, T>;
    } // namespace engine::renderer

#endif