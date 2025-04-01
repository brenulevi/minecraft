#pragma once

class VertexBuffer
{
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void bind();

private:
    unsigned int _Id;
};