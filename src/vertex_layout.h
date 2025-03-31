#pragma once

#include <vector>
#include <glad/glad.h>

struct VertexElement
{
    int count;
    int type;
    unsigned int size_of_type;
};

class VertexLayout
{
public:
    VertexLayout();
    ~VertexLayout();

    template <typename T>
    void push(int count);

    std::vector<VertexElement>& get_elements();
    unsigned int get_stride();

private:
    std::vector<VertexElement> _elements;
    unsigned int _stride;
};

template <typename T>
inline void VertexLayout::push(int count)
{
}

template <>
inline void VertexLayout::push<float>(int count)
{
    _elements.push_back({ count, GL_FLOAT, sizeof(float) });
    _stride += count * sizeof(float);
}
