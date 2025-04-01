#include "VertexBuffer.h"

#include <glad/glad.h>

VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
    glGenBuffers(1, &_Id);

    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &_Id);
}

void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, _Id);
}
