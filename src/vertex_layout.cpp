#include "vertex_layout.h"

VertexLayout::VertexLayout()
    : _stride(0)
{
}

VertexLayout::~VertexLayout()
{
}

std::vector<VertexElement> &VertexLayout::get_elements()
{
    return _elements;
}

unsigned int VertexLayout::get_stride()
{
    return _stride;
}
