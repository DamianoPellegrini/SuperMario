#include "pch.hpp"
#include "vertex_array.hpp"

namespace engine::renderer {
    vertex_array::vertex_array()
        : bound_attribute_index(0), max_vertex_attributes(16) {
        glGenVertexArrays(1, &array_id);
        glGetIntegerv(GL_MAX_VERTEX_ATTRIB_BINDINGS, &max_vertex_attributes);
    }

    vertex_array::~vertex_array() {
        glDeleteVertexArrays(1, &array_id);
    }

    void vertex_array::bind() const {
        glBindVertexArray(array_id);
    }

    void vertex_array::unbind() const {
        glBindVertexArray(0);
    }

    void vertex_array::unbind_element_buffer() const {
        glVertexArrayElementBuffer(array_id, 0);
    }

    void vertex_array::enable_attribute(const size_t index) const {
        glEnableVertexArrayAttrib(array_id, index);
    }

    void vertex_array::disable_attribute(const size_t index) const {
        glDisableVertexArrayAttrib(array_id, index);
    }

} // namespace engine::renderer
