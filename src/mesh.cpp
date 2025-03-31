#include "mesh.h"

#include <glad/glad.h>

Mesh::Mesh(VertexLayout& layout)
    : _index_count(0)
{
    glGenVertexArrays(1, &_vertex_array_id);
    glGenBuffers(1, &_vertex_buffer_id);
    glGenBuffers(1, &_index_buffer_id);

    glBindVertexArray(_vertex_array_id);
    glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);

    auto& elements = layout.get_elements();
    unsigned int offset = 0;
    for(int i = 0; i < elements.size(); i++)
    {
        auto& e = elements[i];
        glVertexAttribPointer(i, e.count, e.type, GL_FALSE, layout.get_stride(), (void*)(offset));
        glEnableVertexAttribArray(i);
        
        offset += e.count * e.size_of_type;
    }
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &_vertex_array_id);
    glDeleteBuffers(1, &_vertex_buffer_id);
    glDeleteBuffers(1, &_index_buffer_id);
}

void Mesh::add_vertices(const void *data, unsigned int size)
{
    glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void Mesh::add_indices(const unsigned int *data, unsigned int size)
{
    _index_count = size / sizeof(unsigned int);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void Mesh::bind()
{
    glBindVertexArray(_vertex_array_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer_id);
}

unsigned int Mesh::get_index_count()
{
    return _index_count;
}
