#pragma once

#include <vector>
#include <glad/glad.h>

struct VertexElement
{
    int count;
    GLenum type;
    unsigned int size;
};

class VertexLayout
{
public:
    VertexLayout();
    ~VertexLayout();

    template <typename T>
    void add(int count);

    inline std::vector<VertexElement> &getElements() { return _Elements; }
    inline unsigned int getStride() { return _Stride; }

private:
    std::vector<VertexElement> _Elements;
    unsigned int _Stride;
};

template <typename T>
inline void VertexLayout::add(int count)
{
}

template <>
inline void VertexLayout::add<float>(int count)
{
    _Elements.push_back({count, GL_FLOAT, sizeof(float)});
    _Stride += count * sizeof(float);
}
