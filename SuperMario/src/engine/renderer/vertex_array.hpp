#ifndef _VERTEX_ARRAY_HPP
#define _VERTEX_ARRAY_HPP

#include "buffer.hpp"
#include "../util.hpp"

namespace engine::renderer {
    class vertex_array {
    private:
        uint32_t array_id;
        int32_t max_vertex_attributes;
    public:
        uint16_t bound_attribute_index;

        vertex_array();
        virtual ~vertex_array();

        void bind() const;
        void unbind() const;

        template<class T>
        void bind_element_buffer(const index_buffer<T>& buffer) const;
        void unbind_element_buffer() const;

        template <class T>
        void define_attribute(const vertex_buffer<T>& buffer, const size_t index, const size_t size, const bool normalized, const size_t stride, const size_t offset);

        void enable_attribute(const size_t index) const;
        void disable_attribute(const size_t index) const;

        inline uint32_t id() const { return array_id; }
    };

    template <class T>
    void vertex_array::bind_element_buffer(const index_buffer<T>& buffer) const {
        glVertexArrayElementBuffer(array_id, buffer.id());
    }

    template <class T>
    void vertex_array::define_attribute(const vertex_buffer<T>& buffer, const size_t index, const size_t size, const bool normalized, const size_t stride, const size_t offset) {
        if (index >= max_vertex_attributes) {
            throw std::runtime_error("Index out of range!");
        }

        // Bind out VBO to that index
        glBindVertexBuffer(this->bound_attribute_index, buffer.id(), offset, stride);

        // Define the format in the VAO
        glVertexArrayAttribFormat(array_id, index, size, util::getGLType<T>(), normalized ? GL_TRUE : GL_FALSE, offset);
        glVertexArrayAttribBinding(array_id, index, this->bound_attribute_index);

        this->bound_attribute_index++;
    }

} // namespace engine::renderer


#endif // _VERTEX_ARRAY_HPP