#include "pch.hpp"
#include "vertex_array.hpp"

namespace engine::renderer {
    vertex_array::vertex_array()
        : max_vertex_attribute_bindings(16), max_vertex_attributes(16) {
        glCreateVertexArrays(1, &(this->array_id));
        glGetIntegerv(GL_MAX_VERTEX_ATTRIB_BINDINGS, &max_vertex_attribute_bindings);
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_vertex_attributes);

        // std::clog << max_vertex_attribute_bindings << " vertex attribute bindings" << std::endl;
        // std::clog << max_vertex_attributes << " vertex attributes" << std::endl;
    }

    vertex_array::~vertex_array() {
        glDeleteVertexArrays(1, &(this->array_id));
    }

    void vertex_array::bind() const {
        glBindVertexArray(this->array_id);
    }

    void vertex_array::unbind() const {
        glBindVertexArray(0);
    }

    void vertex_array::unbind_vertex_buffer(const uint32_t index) const {
        if (index > max_vertex_attribute_bindings) {
            throw std::runtime_error("Index out of range!");
        }
        glVertexArrayVertexBuffer(this->array_id, index, 0, 0, 0);
    }

    void vertex_array::unbind_index_buffer() const {
        glVertexArrayElementBuffer(this->array_id, 0);
    }

    void vertex_array::enable_attribute(const size_t index) const {
        glEnableVertexArrayAttrib(this->array_id, index);
    }

    void vertex_array::disable_attribute(const size_t index) const {
        glDisableVertexArrayAttrib(this->array_id, index);
    }

} // namespace engine::renderer
