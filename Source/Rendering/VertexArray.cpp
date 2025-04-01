#include "VertexArray.h"

#include <glad/glad.h>

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &_Id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &_Id);
}

void VertexArray::addVertexBuffer(VertexLayout &layout, VertexBuffer &buffer)
{
    bind();
    buffer.bind();

    auto& elements = layout.getElements();
    unsigned int offset = 0;

    for(int i = 0; i < elements.size(); i++)
    {
        auto& element = elements[i];
        glVertexAttribPointer(i, element.count, element.type, GL_FALSE, layout.getStride(), (void*) offset);
        glEnableVertexAttribArray(i);

        offset += element.count * element.size;
    }
}

void VertexArray::bind()
{
    glBindVertexArray(_Id);
}
