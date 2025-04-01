#pragma once

#include "VertexLayout.h"
#include "VertexBuffer.h"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void addVertexBuffer(VertexLayout& layout, VertexBuffer& buffer);

    void bind();

private:
    unsigned int _Id;
};