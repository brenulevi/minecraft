#pragma once

#include "vertex_layout.h"

class Mesh
{
public:
    Mesh(VertexLayout& layout);
    ~Mesh();

    void add_vertices(const void* data, unsigned int size);
    void add_indices(const unsigned int* data, unsigned int size);

    void bind();

    unsigned int get_index_count();

private:
    unsigned int _vertex_array_id;
    unsigned int _vertex_buffer_id;
    unsigned int _index_buffer_id;

    unsigned int _index_count;
};