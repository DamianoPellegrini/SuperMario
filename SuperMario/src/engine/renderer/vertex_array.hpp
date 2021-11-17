#ifndef _VERTEX_ARRAY_HPP
#define _VERTEX_ARRAY_HPP

#include "buffer.hpp"
#include "../util.hpp"

namespace engine::renderer {
    class vertex_array {
    private:
        uint32_t array_id;
        int32_t max_vertex_attribute_bindings;
        int32_t max_vertex_attributes;
    public:
        vertex_array();
        virtual ~vertex_array();

        void bind() const;
        void unbind() const;

        template<class T>
        void bind_vertex_buffer(const vertex_buffer<T>& buffer, const uint32_t index, const size_t stride, const uint32_t offset) const;
        void unbind_vertex_buffer(const uint32_t index) const;

        template<class T>
        void bind_index_buffer(const index_buffer<T>& buffer) const;
        void unbind_index_buffer() const;

        template <class T>
        void define_attribute(const vertex_buffer<T>&buffer, const uint32_t index, const size_t count, const bool normalized, const size_t stride, const uint32_t offset) const;

        void enable_attribute(const size_t index) const;
        void disable_attribute(const size_t index) const;

        inline uint32_t id() const { return array_id; }
    };

    template <class T>
    void vertex_array::bind_vertex_buffer(const vertex_buffer<T>& buffer, const uint32_t index, const size_t stride, const uint32_t offset) const {
        if (index > max_vertex_attribute_bindings) {
            throw std::runtime_error("Index out of range!");
        }
        glVertexArrayVertexBuffer(this->array_id, index, buffer.id(), offset, stride);
    }

    template <class T>
    void vertex_array::bind_index_buffer(const index_buffer<T>& buffer) const {
        glVertexArrayElementBuffer(this->array_id, buffer.id());
    }

    template <class T>
    void vertex_array::define_attribute(const vertex_buffer<T>&buffer, const uint32_t index, const size_t count, const bool normalized, const size_t stride, const uint32_t offset) const {
        if (index > max_vertex_attributes) {
            throw std::runtime_error("Index out of range!");
        }

        // Bind VBO to a binding index
        this->bind_vertex_buffer(buffer, index, stride, offset);

        // Define the format in the VAO
        glVertexArrayAttribFormat(this->array_id, index, count, util::getGLType<T>(), normalized ? GL_TRUE : GL_FALSE, 0);
        glVertexArrayAttribBinding(this->array_id, index, index);

    }

} // namespace engine::renderer


#endif // _VERTEX_ARRAY_HPP